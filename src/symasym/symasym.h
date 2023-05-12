#ifndef SYMASYM_H
#define SYMASYM_H

#define PIXEL_SIZE 3 // each pixel contain 3 codes: RGB
#define MAX_FILENAME_SIZE 40

#define WHITE 255
#define BLACK 0 

void generateImages(); // generates n amount of images, n can be retrieved from SConfig.nSize (see /config/config.c)

#endif