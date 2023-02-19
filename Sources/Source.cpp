#include <array>
#include <fstream>
#include <cmath>

#include "Logger.h"
#include "Image.h"
#include "Canvas.h"

auto main() -> int try
{
    auto start = std::chrono::high_resolution_clock::now();

    Hackaton::Canvas canvas {3840, 2160};

    // Draw circle
    canvas.DrawBackground([](double x, double y) -> std::optional<Hackaton::Pixel>
    {
        double r = (x * 2 / 3840);
        double g = ((x + y) * 0.5 / (3840 + 2160));
        double b = (y * 2 / 2160);

        return std::optional { Hackaton::Pixel {
            (std::uint8_t)(Hackaton::Lerp(0.3, 0.7, std::clamp(r, 0.0, 1.0)) * 255),
            (std::uint8_t)(Hackaton::Lerp(0.3, 0.7, std::clamp(g, 0.0, 1.0)) * 255),
            (std::uint8_t)(Hackaton::Lerp(0.3, 0.7, std::clamp(b, 0.0, 1.0)) * 255)
        }};
    });

    // Draw circle
    canvas.DrawShape([x0 = 700, y0 = 700, radius = 300](double x, double y) -> std::optional<Hackaton::Pixel>
    {
        return (std::pow(x - x0, 2) + std::pow(y - y0, 2) <= std::pow(radius, 2))
            ? std::optional{ Hackaton::Pixel::Black() } : std::nullopt;
    });

    // Draw square
    canvas.DrawShape([x0 = 3840 - 700, y0 = 2160 - 700, size = 600](double x, double y) -> std::optional<Hackaton::Pixel>
    {
        return (x <= (x0 + size / 2)
            && x >= (x0 - size / 2)
            && y <= (y0 + size / 2)
            && y >= (y0 - size / 2))
            ? std::optional{ Hackaton::Pixel::Black() } : std::nullopt;
    });

    canvas.ProcessCommands();

    auto end = std::chrono::high_resolution_clock::now();
    Hackaton::Logger::Warning(
        "Generation time " + std::to_string(
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count())
        + "ms");

    Hackaton::BitmapImage image {3840, 2160};
    canvas.Write(image.Data());
    image.Save("Image.bmp");
}
catch (const std::exception& ex)
{
    Hackaton::Logger::Error(ex.what());
}
