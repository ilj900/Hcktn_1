#pragma once

#include <cstdint>
#include <vector>
#include <span>
#include <optional>

#include "Utils.h"

namespace Hackaton
{

class Canvas
{
public:
    Canvas(std::uint32_t width, std::uint32_t height);

    using DrawFn = std::function<std::optional<Pixel>(double, double)>;

    void Write(std::span<std::byte> data) const;
    void DrawShape(DrawFn fn);
    void DrawBackground(DrawFn fn);
    void SetPixel(std::uint32_t x, std::uint32_t y, Pixel p);
    void ProcessCommands();

private:
    static constexpr inline uint8_t BytesPerPixel = 3;

    std::uint32_t mWidth;
    std::uint32_t mHeight;
    std::vector<std::byte> mData;
    std::vector<DrawFn> mDrawCommands;
};

}
