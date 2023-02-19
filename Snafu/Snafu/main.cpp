#include <fstream>
#include "bmpwriter.h"

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
    std::ofstream out( "pic.svg" );
    out << svg;

    PixelMatrix matrix( WIDTH, HEIGHT );
    fillMatrix( matrix );
    Writer writer( matrix );
    writer.save( "pic.bmp" );
    return 0;
}