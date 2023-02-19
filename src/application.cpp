#include "application.h"

#include <chrono>
#include <iostream>

FApplication::FApplication()
{
	Canvas = std::make_shared<FCanvas>(3840, 2160);
}

int FApplication::Run()
{
	auto Start = std::chrono::system_clock::now();

	Canvas->Mandelbrot(3.f, 2.f, -2.f, -1.f);

	auto End = std::chrono::system_clock::now();
	auto Elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(End - Start);
	std::cout << "Time: " << Elapsed.count() << ".ms\n";

	Canvas->Save("Drawing.bmp");

	return 0;
}