#include "Canvas.h"
#include "Logger.h"

#include <cmath>
#include <thread>

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
    std::vector<std::thread> threads;
    std::uint32_t threadCount = std::thread::hardware_concurrency() * 2;

    Logger::Info("Thread count " + std::to_string(threadCount));

    for (std::uint32_t i = 0; i < threadCount; i++)
    {
        threads.emplace_back([id = i, this, threadCount]() {
            std::uint32_t blockSize = mHeight / threadCount;
            std::uint32_t upperBound = blockSize * (id + 1);

            if (id == threadCount - 1) [[unlikely]]
            {
                upperBound = mHeight;
            }

            for (std::uint32_t i = blockSize * id; i < upperBound; i++)
            {
                for (std::uint32_t j = 0; j < mWidth; j++)
                {
                    for (auto it = mDrawCommands.rbegin(); it != mDrawCommands.rend(); it++)
                    {
                        auto pixel = it->operator()(j, i);

                        if (pixel.has_value()) [[unlikely]]
                        {
                            SetPixel(j, i, pixel.value());
                            break;
                        }
                    }
                }
            }
        });
    }

    for (auto& thread: threads) thread.join();

    Logger::Info("Processed draw commands");
}

}