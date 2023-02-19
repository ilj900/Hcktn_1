#include "canvas.h"

#include <ostream>
#include <fstream>

FCanvas::FCanvas(int Width, int Height) :
	Width(Width), Height(Height)
{
	Data.resize(Width * Height);
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			Data[i * Width + j].Red = unsigned char(float(i) / float(Height));
			Data[i * Width + j].Green = unsigned char(float(j) / float(Width));
			Data[i * Width + j].Blue = 62;
		}
	}
}

int FCanvas::Save(const std::string& Path)
{
	FILE* OutpuFile;
	OutpuFile = fopen(Path.c_str(), "wb");

	int WidthInBytes = Width * sizeof(FPoint);

	unsigned char Padding[3] = { 0, 0, 0 };
	int PaddingSize = (4 - (WidthInBytes) % 4) % 4;

	int Stride = (WidthInBytes) + PaddingSize;

	FILE* ImageFile = fopen(Path.c_str(), "wb");

	const int FILE_HEADER_SIZE = 14;
	const int INFO_HEADER_SIZE = 40;

	unsigned char BMPHeader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	int FileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (Stride * Height);
	BMPHeader[2] = (unsigned char)(FileSize);
	BMPHeader[3] = (unsigned char)(FileSize >> 8);
	BMPHeader[4] = (unsigned char)(FileSize >> 16);
	BMPHeader[5] = (unsigned char)(FileSize >> 24);

	fwrite(BMPHeader, 1, FILE_HEADER_SIZE, ImageFile);

	unsigned char BMPInfoHeade[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };

	BMPInfoHeade[4] = (unsigned char)(Width);
	BMPInfoHeade[5] = (unsigned char)(Width >> 8);
	BMPInfoHeade[6] = (unsigned char)(Width >> 16);
	BMPInfoHeade[7] = (unsigned char)(Width >> 24);
	BMPInfoHeade[8] = (unsigned char)(Height);
	BMPInfoHeade[9] = (unsigned char)(Height >> 8);
	BMPInfoHeade[10] = (unsigned char)(Height >> 16);
	BMPInfoHeade[11] = (unsigned char)(Height >> 24);
	fwrite(BMPInfoHeade, 1, INFO_HEADER_SIZE, ImageFile);

	unsigned char BMPPad[3] = { 0,0,0 };

	int i;
	for (i = 0; i < Height; i++) {
		fwrite(Data.data() + (i * Width), sizeof(FPoint), Width, ImageFile);
		fwrite(Padding, 1, PaddingSize, ImageFile);
	}

	fclose(ImageFile);

	return 0;
}

int FCanvas::DrawCircle(float Radius, float X, float Y, float R, float G, float B)
{
	int XStart = X - (Radius);
	int XEnd = X + (Radius);
	XStart = XStart < 0 ? 0 : XStart;
	XEnd = XEnd > Width ? Width : XEnd;
	int YStart = Y - (Radius);
	int YEnd = Y + (Radius);
	YStart = YStart < 0 ? 0 : YStart;
	YEnd = YEnd > Height ? Height : YEnd;

	char Red = char(R * 255.f);
	char Green = char(G * 255.f);
	char Blue = char(B * 255.f);

	float R2 = Radius * Radius;

	for (int i = XStart; i < XEnd; ++i)
	{
		for (int j = YStart; j < YEnd; ++j)
		{
			float PixelX = i;
			float PixelY = j;
			float Length2 = (PixelX - X) * (PixelX - X) + (PixelY - Y) * (PixelY - Y);

			if (Length2 < R2)
			{
				Data[j * Width + i].Red = Red;
				Data[j * Width + i].Green = Green;
				Data[j * Width + i].Blue = Blue;
			}
		}
	}

	return 0;
}


int FCanvas::DrawQuad(float A, float X, float Y, float R, float G, float B)
{
	int XStart = X - (A / 2);
	int XEnd = X + (A / 2);
	XStart = XStart < 0 ? 0 : XStart;
	XEnd = XEnd > Width ? Width : XEnd;
	int YStart = Y - (A / 2);
	int YEnd = Y + (A / 2);
	YStart = YStart < 0 ? 0 : YStart;
	YEnd = YEnd > Height ? Height : YEnd;

	char Red = char(R * 255.f);
	char Green = char(G * 255.f);
	char Blue = char(B * 255.f);

	for (int i = XStart; i < XEnd; ++i)
	{
		for (int j = YStart; j < YEnd; ++j)
		{
			Data[j * Width + i].Red = Red;
			Data[j * Width + i].Green = Green;
			Data[j * Width + i].Blue = Blue;
		}
	}

	return 0;

}

int FCanvas::CalculateMandelbrotPoint(float x, float y)
{
	float XPrev = x;
	float YPrev = y;

	for (int i = 0; i < MaxIterations; ++i)
	{
		float X2 = XPrev * XPrev;
		float Y2 = YPrev * YPrev;
		if (X2 + Y2 > 4)
		{
			return i;
		}
		float XTmp = X2 - Y2 + x;
		float YTmp = 2.f * XPrev * YPrev + y;
		XPrev = XTmp;
		YPrev = YTmp;
	}

	return MaxIterations;
}


int FCanvas::Mandelbrot(float AreaWidth, float AreaHeight, float StartingPointX, float StartingPointY)
{
	float XStep = AreaWidth / float(Width);
	float YStep = AreaHeight / float(Height);
	for (int i = 0; i < Width; ++i)
	{
		for (int j = 0; j < Height; ++j)
		{
			float x = StartingPointX + ((float(i) + 0.5f) * XStep);
			float y = StartingPointY + ((float(j) + 0.5f) * YStep);
			int Count = CalculateMandelbrotPoint(x, y);
			if (Count >= 64)
			{
				float RedVal = float(Count / 32) / (float(Count % 32) + 1.f);
				float GreenVal = float(Count % 32) / (float(Count % 32) + 1.f);

				Data[j * Width + i].Red = RedVal * 255;
				Data[j * Width + i].Green = GreenVal * 255;
				Data[j * Width + i].Blue = 128;
			}
			else
			{
				Data[j * Width + i].Red = 225;
				Data[j * Width + i].Green = 128;
				Data[j * Width + i].Blue = 0;
			}
		}
	}

	return 0;

}