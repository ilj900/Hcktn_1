#include <fstream>
#include <iostream>
#include "bmpwriter.h"
#include <ctime>
#include <complex>

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

void mandelbrot( PixelMatrix& matrix )
{
    using namespace std::complex_literals;
    for ( size_t k = 0; k < HEIGHT; k++ )
        for ( size_t j = 0; j < WIDTH; j++ )
        {
            std::complex<double> c = -2.0 + 3.0 * j / ( WIDTH - 1 ) - 1.0i + 2.0i * (double) k / (double) ( HEIGHT - 1 );
            std::complex<double> z = c;
            for ( int n = 1; n < 50 && abs( z ) < 2.0; ++n )
            {
                z = z * z + c;
            }
            matrix.set( k, j, abs( z ) < 2.0 );
        }
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

    PixelMatrix matrix2( WIDTH, HEIGHT );
    mandelbrot( matrix2 );
    Writer writer2( matrix2 );
    writer2.save( "mand.bmp" );


    double t = (double) ( finish - start ) / CLK_TCK;
    std::cout << t << std::endl;
    return 0;
}