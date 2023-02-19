#pragma once

#include <cstdint>
#include <memory>

namespace Hackaton
{

struct Pixel
{
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;

    void Write(void* location);

    static Pixel White();
    static Pixel Black();
};

float Lerp(float a, float b, float t);

}