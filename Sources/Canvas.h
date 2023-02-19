#pragma once

#include <cstdint>
#include <vector>
#include <span>

#include "Utils.hpp"

namespace Hackaton
{

class Canvas
{
public:
    Canvas(std::uint32_t width, std::uint32_t height);
    void Write(std::span<std::byte> data) const;
    void DrawShape(std::function<bool(double, double)> fn);
    void DrawBackground(std::function<Pixel(double, double)> fn);
    void SetPixel(std::uint32_t x, std::uint32_t y, Pixel p);

private:
    static constexpr inline uint8_t BytesPerPixel = 3;

    std::uint32_t mWidth;
    std::uint32_t mHeight;
    std::vector<std::byte> mData;
};

}
