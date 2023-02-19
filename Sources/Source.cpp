#include <array>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include "Logger.h"
#include "Image.h"
#include "Canvas.h"
#include "Mandlebrot.h"

auto main() -> int try
{
    Hackaton::BitmapImage image {3840, 2160};
    Hackaton::Canvas canvas {3840, 2160};
    srand(time(0));

    auto start = std::chrono::high_resolution_clock::now();

    // Draw circle
    canvas.DrawBackground([](double x, double y) -> std::optional<Hackaton::Pixel>
    {
        double r = (x * 2 / 3840);
        double g = ((x + y) * 0.5 / (3840 + 2160));
        double b = (y * 2 / 2160);

        return std::optional { Hackaton::Pixel {
            (std::uint8_t)(Hackaton::Lerp(0.1, 0.6, std::clamp(r, 0.0, 1.0)) * 255),
            (std::uint8_t)(Hackaton::Lerp(0.1, 0.6, std::clamp(g, 0.0, 1.0)) * 255),
            (std::uint8_t)(Hackaton::Lerp(0.1, 0.6, std::clamp(b, 0.0, 1.0)) * 255)
        }};
    });

    // Draw circle
    /*canvas.DrawShape([radius = 300, x0 = 2400, y0 = 1200](double x, double y) -> std::optional<Hackaton::Pixel>
    {
        double distance = 1.0 - std::sqrt(std::pow(x - x0, 2) + std::pow(y - y0, 2)) / radius / 2;
        auto d = (std::uint8_t)(Hackaton::Lerp(0.0, 0.2, std::clamp(distance, 0.0, 1.0)) * 255);
        return (std::pow(x - x0, 2) + std::pow(y - y0, 2) <= std::pow(radius, 2))
            ? std::optional{ Hackaton::Pixel {d, d, d} } : std::nullopt;
    });*/

    // Draw square
    /*canvas.DrawShape([x0 = 1200, y0 = 1200, size = 600](double x, double y) -> std::optional<Hackaton::Pixel>
    {
        double distance = 1.0 - std::sqrt(std::pow(x - x0, 2) + std::pow(y - y0, 2)) / size / 1.5;
        auto d = (std::uint8_t)(Hackaton::Lerp(0.0, 0.2, std::clamp(distance, 0.0, 1.0)) * 255);
        return (x <= (x0 + size / 2)
            && x >= (x0 - size / 2)
            && y <= (y0 + size / 2)
            && y >= (y0 - size / 2))
            ? std::optional{ Hackaton::Pixel {d, d, d} } : std::nullopt;
    });*/

    // Mandlebrot
    canvas.DrawShape([](double x, double y) -> std::optional<Hackaton::Pixel>
    {
        std::uint32_t value = Hackaton::Mandlebrot::IsPointDiverge({(float)x / 1024 - 2.5f, (float)y / 1024 - 1});

        if (value == 0)
        {
            return std::optional { Hackaton::Pixel::Black() };
        }
        else
        {
            return std::nullopt;
        }
    });

    canvas.ProcessCommands();

    auto end = std::chrono::high_resolution_clock::now();

    Hackaton::Logger::Warning(
        "Generation time " + std::to_string(
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count())
        + "ms");

    canvas.Write(image.Data());
    image.Save("Image.bmp");
}
catch (const std::exception& ex)
{
    Hackaton::Logger::Error(ex.what());
}
