#include "application.h"

FApplication::FApplication()
{
	Canvas = std::make_shared<FCanvas>(3840, 2160);
}

int FApplication::Run()
{
	// Draw Circle
	Canvas->DrawQuad(400, 500, 500, 0.3f, 0.3f, 0.9f);

	Canvas->DrawCircle(400, 1200, 1200, 0.3f, 0.3f, 0.9f);

	Canvas->Save("Drawing.bmp");

	return 0;
}