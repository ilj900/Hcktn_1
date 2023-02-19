#include "Mandlebrot.h"

#include "Logger.h"

namespace Hackaton
{

std::uint32_t
Mandlebrot::IsPointDiverge(const std::complex<float>& point)
{
    std::complex<float> currentValue = 0;

    for (std::uint32_t i = 0; i < 20; i++)
    {
        currentValue = std::pow(currentValue, 2.0f) + point;

        if (auto value = std::abs(currentValue); value >= 2.0f)
        {
            return i;
        }
    }

    return 0;
}

}