#pragma once

#include <cstdint>
#include <filesystem>

namespace Hackaton
{

class BitmapImage
{
public:
    BitmapImage(std::uint32_t width, std::uint32_t height);
    void Save(const std::filesystem::path& location);

private:
    std::uint32_t mWidth;
    std::uint32_t mHeight;
};

}
