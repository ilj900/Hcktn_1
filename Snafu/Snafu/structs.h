#pragma once
#include <cstdint>

struct bmpfile_header
{
    uint16_t magic = 0x4D42; // 'BM'
    uint32_t file_size;
    uint32_t : 32;
    uint32_t bmp_offset;
};

struct bmpfile_dib_info
{
    uint32_t header_size;
    int32_t  width;
    int32_t  height;
    uint16_t num_planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t bmp_byte_size;
    int32_t  hres;
    int32_t  vres;
    uint32_t num_colors;
    uint32_t num_important_colors;
};

struct bmpfile_color_table
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t : 8;
};