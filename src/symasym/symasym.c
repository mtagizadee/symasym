#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "symasym.h"
#include "../config/config.h"
#include "../random/random.h"

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

unsigned char*** pppPixels;

void initPixels(void);
void freePixels(void);
void saveBMPImage(void);
void generateOutputName(char sOut[]);
void generatePixels(void);


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

    fwrite(&bmpHeader, sizeof(SBMPImage), 1, pFile); // Write the BMP header
    for (int i = 0; i < pConf->nSize; i++) {
        for (int j = 0; j < pConf->nSize; j++) {
            fwrite(pppPixels[i][j], PIXEL_SIZE, 1, pFile); // Write the pixel data
        }
    }

    fwrite(pppPixels, 1, nImageSize, pFile); // Write the pixel data
    fclose(pFile);
}

void generateImages() {
    SConfig* pConf = getConfig();
    
    // generate n images 
    for (int i = 0; i < pConf->n; i++) {
        
        if (i != 0 && !pConf->fSeedProvided) { // in order to prevent all images bee the same
            int nNewSeed = getRandSeed();
            
            setRandSeed(nNewSeed); // change the rand see to prevent random repetitions
            changeSeed(nNewSeed); // change the image seed
        }

        initPixels();
        generatePixels();
        saveBMPImage();
        freePixels();
    }
}

void initPixels() {
    int nSize = getConfig()->nSize;

    // dynamically allocate memory of pixels array
    pppPixels = malloc(nSize * sizeof(unsigned char**));
    for (int i = 0; i < nSize; i++) {
        pppPixels[i] = malloc(nSize * sizeof(unsigned char*));

        for (int j = 0; j < nSize; j++) {
            pppPixels[i][j] = malloc(PIXEL_SIZE * sizeof(unsigned char));    
            for (int k = 0; k < PIXEL_SIZE; k++) {
                pppPixels[i][j][k] = WHITE; // At the beginning BMP image should be fully white and empty
            }
        }
    }
}

void freePixels() {
    int nSize = getConfig()->nSize;
    
    for (int i = 0; i < nSize; i++) {
        for (int j = 0; j < nSize; j++) free(pppPixels[i][j]);
        free(pppPixels[i]);
    }
    free(pppPixels);
}

void generatePixels() {
    SConfig* pConf = getConfig();
}

void generateOutputName(char sOut[]) {
    SConfig* pConf = getConfig();
    if (pConf->o != NULL) strcpy(sOut, pConf->o);
    else {
        char* sRes = malloc(2 * sizeof(char*));
        switch (pConf->asstype)
        {
            case asymmetric: 
                sRes[0] = 'a';
                break;
            case symmetric: 
                sRes[0] = 's';
                break;
            default: 
                break;
        }

        switch (pConf->vhtype)
        {
            case vertical: 
                sRes[1] = 'v';
                break;
            case horizontal: 
                sRes[1] = 'h';
                break;
            default: 
                break;
        }
        
        strcpy(sOut, sRes);
    }

    strcat(sOut, ".bmp");
}