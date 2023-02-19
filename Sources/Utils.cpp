#include "Utils.h"

#include <cstdint>
#include <memory>

namespace Hackaton
{

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

}