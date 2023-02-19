#include "Utils.h"

#include <cstdint>
#include <memory>

namespace Hackaton
{

void 
Pixel::Write(void* location)
{
    std::memcpy(location, this, sizeof(Pixel));
}

Pixel
Pixel::White()
{
    return {255, 255, 255};
}

Pixel
Pixel::Black()
{
    return {0, 0, 0};
}

float Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

}