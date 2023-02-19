#pragma once

#include <cstdint>
#include <memory>

namespace Hackaton
{

struct Pixel
{
    std::uint8_t b;
    std::uint8_t g;
    std::uint8_t r;

    void Write(void* location);

    static Pixel White();
    static Pixel Black();
};

inline void
Pixel::Write(void* location)
{
    std::memcpy(location, this, sizeof(Pixel));
}

inline float Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

}