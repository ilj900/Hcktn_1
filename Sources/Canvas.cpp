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
Canvas::DrawShape(
    std::function<bool(double, double)> fn,
    const Pixel& color)
{
    for (std::size_t i = 0; i < mHeight; i++)
    {
        for (std::size_t j = 0; j < mWidth; j++)
        {
            if (fn(j, i))
            {
                SetPixel(j, i, color);
            }
        }
    }

    Logger::Info("Drawn shape");
}

void
Canvas::DrawBackground(std::function<Pixel(double, double)> fn)
{
    for (std::size_t i = 0; i < mHeight; i++)
    {
        for (std::size_t j = 0; j < mWidth; j++)
        {
            SetPixel(j, i, fn(j, i));
        }
    }

    Logger::Info("Drawn background");
}

void 
Canvas::SetPixel(std::uint32_t x, std::uint32_t y, Pixel p)
{
    p.Write(mData.data() + (y * mWidth + x) * Canvas::BytesPerPixel);
}

}