#include "bmpwriter.h"
#include <fstream>

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

size_t PixelMatrix::width() const
{
    return width_;
}

size_t PixelMatrix::height() const
{
    return height_;
}

Writer::Writer( const PixelMatrix& mat ) :
    matrix_{ mat }
{}

bool Writer::save( std::string filename )
{
    std::ofstream file( filename );

    bmpfile_header header {};
    header.bmp_offset = sizeof( bmpfile_header ) + sizeof( bmpfile_dib_info ) + sizeof( bmpfile_color_table );
    header.file_size = header.bmp_offset + matrix_.width() * matrix_.height() / 8;
    file.write( (char*) ( &header ), sizeof( header ) );

    bmpfile_dib_info dib_info {};
    dib_info.header_size = sizeof( bmpfile_dib_info );
    dib_info.width = matrix_.width();
    dib_info.height = matrix_.height();
    dib_info.num_planes = 1;
    dib_info.bits_per_pixel = 1;  // monochrome
    dib_info.compression = 0;
    dib_info.bmp_byte_size = 0;
    dib_info.hres = 200;
    dib_info.vres = 200;
    dib_info.num_colors = 1;
    dib_info.num_important_colors = 0;
    file.write( (char*) ( &dib_info ), sizeof( dib_info ) );

    return true;
}
