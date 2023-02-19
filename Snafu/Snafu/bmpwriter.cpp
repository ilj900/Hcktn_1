#include "bmpwriter.h"
#include <fstream>

PixelMatrix::PixelMatrix( size_t width, size_t height ) :
    width_{ width }, height_{ height }
{
    pixels_.assign( width * height, true );
}

void PixelMatrix::set( size_t x, size_t y, bool value )
{
    pixels_[x * width_ + y] = value;
}

bool PixelMatrix::get( size_t x, size_t y ) const
{
    return pixels_[x * width_ + y];
}

size_t PixelMatrix::width() const
{
    return width_;
}

size_t PixelMatrix::height() const
{
    return height_;
}

char PixelMatrix::getByte( size_t num ) const
{
    char result{};
    size_t base = num * 8;
    for ( int i = 0; i < 8; i++ )
    {
        result += pixels_[base + i] << ( 7 - i );
    }
    return result;
}

Writer::Writer( const PixelMatrix& mat ) :
    matrix_{ mat }
{}

bool Writer::save( std::string filename )
{
    std::ofstream file( filename );
    const size_t matrixBytes = matrix_.width() * matrix_.height() / 8;

    bmpfile_header header {};
    header.bmp_offset = sizeof( bmpfile_header ) + sizeof( bmpfile_dib_info ) + 2 * sizeof( bmpfile_color_table );
    header.file_size = header.bmp_offset + matrixBytes;
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
    dib_info.num_colors = 2;
    dib_info.num_important_colors = 0;
    file.write( (char*) ( &dib_info ), sizeof( dib_info ) );

    bmpfile_color_table off_color{};
    off_color.red = 0;
    off_color.green = 0;
    off_color.blue = 0;
    file.write( (char*) ( &off_color ), sizeof( off_color ) );

    bmpfile_color_table on_color{};
    on_color.red = 0xFF;
    on_color.green = 0xFF;
    on_color.blue = 0xFF;
    file.write( (char*) ( &on_color ), sizeof( on_color ) );

    for ( size_t num = 0; num < matrixBytes; ++num )
    {
        char c = matrix_.getByte( num );
        file.write( &c, 1 );
    }
    return true;
}
