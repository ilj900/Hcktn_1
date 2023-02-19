#include "Image.h"
#include "Logger.h"

#include <fstream>
#include <stdio.h>

namespace Hackaton
{

BitmapImage::BitmapImage(std::uint32_t width, std::uint32_t height)
    : mWidth(width)
    , mHeight(height)
{
    mData.resize(BitmapImage::BytesPerPixel * width * height);

    for (std::size_t i = 0; i < mHeight; i++) {
        for (std::size_t j = 0; j < mWidth; j++) {
            mData[i*mWidth*BytesPerPixel+j*BytesPerPixel+2] = (std::byte) ( i * 255 / mHeight );             ///red
            mData[i*mWidth*BytesPerPixel+j*BytesPerPixel+1] = (std::byte) ( j * 255 / mWidth );              ///green
            mData[i*mWidth*BytesPerPixel+j*BytesPerPixel+0] = (std::byte) ( (i+j) * 255 / (mHeight+mWidth) ); ///blue
        }
    }
}

std::array<std::byte, BitmapImage::FileHeaderSize> 
BitmapImage::GenerateBitmapFileHeader (std::size_t fileSize)
{
    std::array<std::byte, BitmapImage::FileHeaderSize> header;
    header.fill({});

    header[ 0] = (std::byte)('B');
    header[ 1] = (std::byte)('M');
    header[ 2] = (std::byte)(fileSize      );
    header[ 3] = (std::byte)(fileSize >>  8);
    header[ 4] = (std::byte)(fileSize >> 16);
    header[ 5] = (std::byte)(fileSize >> 24);
    header[10] = (std::byte)(BitmapImage::FileHeaderSize + BitmapImage::InfoHeaderSize);

    return header;
}

std::array<std::byte, BitmapImage::InfoHeaderSize> 
BitmapImage::GenerateBitmapInfoHeader()
{
    std::array<std::byte, BitmapImage::InfoHeaderSize> header;
    header.fill({});

    header[ 0] = (std::byte)(BitmapImage::InfoHeaderSize);
    header[ 4] = (std::byte)(mWidth      );
    header[ 5] = (std::byte)(mWidth >>  8);
    header[ 6] = (std::byte)(mWidth >> 16);
    header[ 7] = (std::byte)(mWidth >> 24);
    header[ 8] = (std::byte)(mHeight      );
    header[ 9] = (std::byte)(mHeight >>  8);
    header[10] = (std::byte)(mHeight >> 16);
    header[11] = (std::byte)(mHeight >> 24);
    header[12] = (std::byte)(1);
    header[14] = (std::byte)(BitmapImage::BytesPerPixel*8);

    return header;
}

void
BitmapImage::Save(const std::filesystem::path& location)
{
    std::ofstream file{location, std::ios::binary};

    uint32_t widthInBytes = mWidth * BitmapImage::BytesPerPixel;

    std::byte padding[3] = {(std::byte)0, (std::byte)0, (std::byte)0};
    uint32_t paddingSize = (4 - (widthInBytes) % 4) % 4;

    uint32_t stride = (widthInBytes) + paddingSize;
    uint32_t fileSize = BitmapImage::FileHeaderSize + BitmapImage::InfoHeaderSize + (stride * mHeight);

    auto fileHeader = GenerateBitmapFileHeader(fileSize);
    file.write((char*)fileHeader.data(), BitmapImage::FileHeaderSize);

    auto infoHeader = GenerateBitmapInfoHeader();
    file.write((char*)infoHeader.data(), BitmapImage::InfoHeaderSize);

    for (std::uint32_t i = 0; i < mHeight; i++) {
        file.write((char*)mData.data() + (i*widthInBytes), BitmapImage::BytesPerPixel * mWidth);
        file.write((char*)padding, paddingSize);
    }
}

}
