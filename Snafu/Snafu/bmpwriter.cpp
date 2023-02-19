#include "bmpwriter.h"

PixelMatrix::PixelMatrix( size_t width, size_t height ) :
    width_{ width }, height_{ height }
{
    pixels_.assign( width * height, false );
}

void PixelMatrix::set( size_t x, size_t y, bool value )
{
    pixels_[x * height_ + y] = value;
}

bool PixelMatrix::get( size_t x, size_t y ) const
{
    return pixels_[x * height_ + y];
}

Writer::Writer( const PixelMatrix& mat ) :
    matrix_{ mat }
{}

bool Writer::save( std::string filename )
{
    return true;
}
