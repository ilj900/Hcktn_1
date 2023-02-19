#pragma once

#include <complex>

namespace Hackaton
{

class Mandlebrot
{
public:
    static std::uint32_t IsPointDiverge(const std::complex<float>& point);
};

}