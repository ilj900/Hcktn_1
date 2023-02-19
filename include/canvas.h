#pragma once

#include <string>
#include <vector>

struct FPoint
{
	unsigned char Red = 255;
	unsigned char Green = 0;
	unsigned char Blue = 255;
};

class FCanvas
{
public:
	FCanvas(int Width, int Height);
	int Save(const std::string& Path);
	int DrawCircle(float Radius, float X, float Y, float R, float G, float B);
	int DrawQuad(float A, float X, float Y, float R, float G, float B);

private:
	int Width;
	int Height;

	std::vector<FPoint> Data;
};