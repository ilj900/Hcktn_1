#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>
#include <array>

namespace Hackaton
{

class BitmapImage
{
public:
    BitmapImage(std::uint32_t width, std::uint32_t height);
    void Save(const std::filesystem::path& location);

private:
    std::uint32_t mWidth;
    std::uint32_t mHeight;
    std::vector<std::byte> mData;

    static constexpr inline uint8_t BytesPerPixel = 3;
    static constexpr inline uint8_t FileHeaderSize = 14;
    static constexpr inline uint8_t InfoHeaderSize = 40;

    std::array<std::byte, BitmapImage::InfoHeaderSize> GenerateBitmapInfoHeader();
    std::array<std::byte, BitmapImage::FileHeaderSize> GenerateBitmapFileHeader(std::size_t fileSize);
};

}
