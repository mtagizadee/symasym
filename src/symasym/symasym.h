#ifndef SYMASYM_H
#define SYMASYM_H

#include <stdint.h>

#define PIXEL_SIZE 3 // each pixel contain 3 codes: RGB
#define THICKNESS 3 // line thickness should be 3 pixels
#define MAX_FILENAME_SIZE 40
#define PADDING_IDENTIFIER 4 // identifies the padding, 4 because we have 4-type image

#define WHITE 255
#define BLACK 0 

#pragma pack(push, 1)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t total_colors;
    uint32_t important_colors;    
} SBMPImage;
#pragma pack(pop)

void generateImages(); // generates n amount of images, n can be retrieved from SConfig.nSize (see /config/config.c)

#endif