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

	Canvas->DrawQuad(400, 500, 500, 0.3f, 0.3f, 0.9f);

	Canvas->DrawCircle(400, 1200, 1200, 0.3f, 0.3f, 0.9f);

	auto End = std::chrono::system_clock::now();
	auto Elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(End - Start);
	std::cout << "Time: " << Elapsed.count() << ".ms\n";

	Canvas->Save("Drawing.bmp");

	return 0;
}