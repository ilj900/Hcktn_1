#pragma once
#include "structs.h"
#include <vector>
#include <string>

class PixelMatrix
{
public:
    PixelMatrix( size_t width, size_t height );
    void set( size_t x, size_t y, bool value = true );
    bool get( size_t x, size_t y ) const;
    size_t width() const;
    size_t height() const;
    char getByte( size_t num ) const;
private:
    std::vector<bool> pixels_;
    size_t width_;
    size_t height_;
};

class Writer
{
public:
    Writer( const PixelMatrix& mat );
    bool save( std::string filename );
private:
    const PixelMatrix& matrix_;
};