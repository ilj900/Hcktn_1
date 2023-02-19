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

float Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

}