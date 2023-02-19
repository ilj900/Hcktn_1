#include <fstream>
#include <iostream>
#include "bmpwriter.h"
#include <ctime>

constexpr const char* svg = 
    "<svg width=\"3840\" height=\"2160\" viewBox=\"0 0 3840 2160\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\">\n"
    "<rect x=\"200\" y=\"200\" width=\"600\" height=\"600\" stroke=\"black\"/>\n"
    "<circle cx=\"500\" cy=\"500\" r=\"200\" stroke=\"green\"/>\n"
    "</svg>";

constexpr size_t WIDTH = 3840, HEIGHT = 2160;

void fillMatrix( PixelMatrix& matrix )
{
    for ( size_t i = 1000; i < 1800; i++ )
        for ( size_t j = 500; j < 1300; j++ )
            matrix.set( i, j );

    for ( size_t i = 0; i < HEIGHT; i++ )
        for ( size_t j = 0; j < WIDTH; j++ )
            if ( ( i - 1400 ) * ( i - 1400 ) + ( j - 1900 ) * ( j - 1900 ) < 400 * 400 )
                matrix.set( i, j );
}

int main()
{
    clock_t start = 0, finish = 0;

    std::ofstream out( "pic.svg" );
    out << svg;

    start = clock();
    PixelMatrix matrix( WIDTH, HEIGHT );
    fillMatrix( matrix );
    finish = clock();
    Writer writer( matrix );
    writer.save( "pic.bmp" );
    double t = (double) ( finish - start ) / CLK_TCK;
    std::cout << t << std::endl;
    return 0;
}