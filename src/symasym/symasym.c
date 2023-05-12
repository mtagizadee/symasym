#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "symasym.h"
#include "../config/config.h"

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



void initPixels(unsigned char cPixels[][MAX_IMAGE_SIZE][PIXEL_SIZE]);
void saveBMPImage();
void generateOutputName(char sOut[]);

void saveBMPImage() {
    SConfig* pConf = getConfig();
    int nImageSize = pConf->nSize * pConf->nSize * PIXEL_SIZE;

    SBMPImage bmpHeader = {
        .type = 0x4D42,             // BM
        .size = 54 + nImageSize,    // Header size + image data size
        .reserved1 = 0,
        .reserved2 = 0,
        .offset = 54,               // Header size
        .header_size = 40,          // Info header size
        .width = pConf->nSize,
        .height = pConf->nSize,
        .planes = 1,
        .bits_per_pixel = 24,       // 24-bit RGB
        .compression = 0,
        .image_size = nImageSize,
        .x_pixels_per_meter = 0,
        .y_pixels_per_meter = 0,
        .total_colors = 0,
        .important_colors = 0
    };

    // Open the file for writing
    char sOut[MAX_FILENAME_SIZE];
    generateOutputName(sOut); // generate file name with respect to configuration
    FILE* pFile = fopen(sOut, "wb");
    if (pFile == NULL) { // validate the file
        printf("Error opening file: %s\n", sOut);
        return;
    }

    int nSize = pConf->nSize;
    unsigned char cPixels[pConf->nSize][pConf->nSize][PIXEL_SIZE];
    for (int i = 0; i < nSize; i++) {
      for (int j = 0; j < nSize; j++) {
          cPixels[i][j][0] = WHITE;
          cPixels[i][j][1] = WHITE;     
          cPixels[i][j][2] = WHITE; 
      }
    }
    
    fwrite(&bmpHeader, sizeof(SBMPImage), 1, pFile); // Write the BMP header
    fwrite(cPixels, 1, nImageSize, pFile); // Write the pixel data
    fclose(pFile);
}

void generateImages() {
    SConfig* pConf = getConfig();
    printf("%s\n",pConf->o);
    
    // unsigned char cPixels[pConf->nSize][pConf->nSize][PIXEL_SIZE];
    // initPixels(cPixels, pConf);
    saveBMPImage(pConf);

    printf("White BMP image generated successfully.\n");
}

void initPixels(unsigned char cPixels[][MAX_IMAGE_SIZE][PIXEL_SIZE]) {
    SConfig* pConf = getConfig();
    // At the beginning BMP image should be fully white and empty
    int nSize = pConf->nSize;
    for (int i = 0; i < nSize; i++) {
        for (int j = 0; j < nSize; j++) {
            cPixels[i][j][0] = WHITE;
            cPixels[i][j][1] = WHITE;     
            cPixels[i][j][2] = WHITE; 
        }
    }
}

void generatePixels(unsigned char cPixels[][MAX_IMAGE_SIZE][PIXEL_SIZE], SConfig* pConf) {

}

void generateOutputName(char sOut[]) {
    SConfig* pConf = getConfig();
    if (pConf->o != NULL) strcpy(sOut, pConf->o);
    else {
        switch (pConf->asstype)
        {
            case asymmetric: 
                strcat(sOut, "a");
                break;
            case symmetric: 
                strcat(sOut, "s"); 
                break;
            default: 
                break;
        }

        switch (pConf->vhtype)
        {
            case vertical: 
                strcat(sOut, "v");
                break;
            case horizontal: 
                strcat(sOut, "h");
                break;
            default: 
                break;
        }
    }

    strcat(sOut, ".bmp");
}