#include <iostream>
#include "EasyBMP.hpp"
#include <vector>
#include <cmath>
using namespace std;

int main()
{
  EasyBMP::Image img(3840, 2160, "sample.bmp", EasyBMP::RGBColor(255, 255, 0));
  for (int y = 1000; y < 2000; ++y) {
    for (int x = 1000; x < 2000; ++x) {
        img.SetPixel(x, y, EasyBMP::RGBColor(0, 255, 0));
    }
  }
  img.DrawCircle(512, 512, 512, EasyBMP::RGBColor(0, 255, 0), true);
  img.Write();
  return 0;
}