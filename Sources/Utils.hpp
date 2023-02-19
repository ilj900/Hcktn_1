#include <cstdint>

#include <memory>

namespace Hackaton
{

struct Pixel
{
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;

    void Write(void* location)
    {
        std::memcpy(location, this, sizeof(Pixel));
    }
};

}