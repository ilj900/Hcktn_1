#include <array>
#include <fstream>

#include "Logger.h"
#include "Image.h"

auto main() -> int
{
    using namespace Hackaton;

    Logger::Info("Hello, world");
    Logger::Warning("Hello, world");
    Logger::Error("Hello, world");

    BitmapImage image {3840, 2160};
    image.Save("Image1.bmp");
}
