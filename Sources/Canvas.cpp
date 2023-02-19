#include "Canvas.h"
#include "Logger.h"

#include <cmath>

namespace Hackaton
{

Canvas::Canvas(std::uint32_t width, std::uint32_t height)
    : mWidth(width)
    , mHeight(height)
    , mData(Canvas::BytesPerPixel * width * height)
{}

void 
Canvas::Write(std::span<std::byte> data) const
{
    if (data.size() != mData.size())
    {
        throw std::runtime_error("Image has different size or components count");
    }

    std::memcpy(data.data(), mData.data(), Canvas::BytesPerPixel * mWidth * mHeight);

    Logger::Info("Copied canvas contents to image");
}

void
Canvas::DrawShape(DrawFn fn)
{
    mDrawCommands.push_back(fn);
}

void
Canvas::DrawBackground(DrawFn fn)
{
    mDrawCommands.push_back(fn);
}

inline void 
Canvas::SetPixel(std::uint32_t x, std::uint32_t y, Pixel p)
{
    p.Write(mData.data() + (y * mWidth + x) * Canvas::BytesPerPixel);
}

void
Canvas::ProcessCommands()
{
    for (std::size_t i = 0; i < mHeight; i++)
    {
        for (std::size_t j = 0; j < mWidth; j++)
        {
            for (auto it = mDrawCommands.rbegin(); it != mDrawCommands.rend(); it++)
            {
                auto pixel = it->operator()(j, i);
                
                if (pixel.has_value())
                {
                    SetPixel(j, i, pixel.value());
                    break;
                }
            }
        }
    }

    Logger::Info("Drawn shape");
}

}