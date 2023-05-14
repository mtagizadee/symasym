#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symasym.h"
#include "../config/config.h"
#include "../random/random.h"

unsigned char*** pppPixels;

void initPixels(void);
void freePixels(void);
void saveBMPImage(void);
void generateOutputName(char sOut[]);
void generatePixels(void);
void insertPixel(int x, int y, int nColor /* either WHITE or BLACK*/); 
void drawLine(int x, int y, int nColor, int fIsVertical);

void saveBMPImage() {
    SConfig* pConf = getConfig();

    int nRowSize = pConf->nSize * PIXEL_SIZE;
    int nPaddingSize = (PADDING_IDENTIFIER - (nRowSize % PADDING_IDENTIFIER)) % PADDING_IDENTIFIER; // Calculate padding size with respect to 4-type image

    int nImageSize = (nRowSize + nPaddingSize) * pConf->nSize;

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

        // Add padding bytes
        for (int p = 0; p < nPaddingSize; p++) {
            fputc(0, pFile);
        }
    }

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
            insertPixel(j, i, WHITE); // At the beginning BMP image should be fully white and empty
        }
    }
}

void insertPixel(int x, int y, int nColor) {
    for (int k = 0; k < PIXEL_SIZE; k++) {
        pppPixels[y][x][k] = nColor;
    }
}

void drawLine(int x, int y, int nColor, int fIsVertical) {
    for (int i = 0; i < THICKNESS; i++) { // respec the thinkness of the line  
        int iCol = fIsVertical? x + i : x;
        int iRow = fIsVertical? y : y + i;
        insertPixel(iCol, iRow, BLACK);
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
    
    // i stands for the index
    int nSize = pConf->nSize;
    int iStartPosition = (pConf->nSeed % (nSize - THICKNESS + 1)); // starting position will be between 0a and nSize - 4, including thickness

    int fIsVertical = pConf->vhtype == vertical;
    int fIsAssym = pConf->asstype == asymmetric;
    int nEnd = fIsAssym? nSize : nSize / 2; // if the image is symmetric then we need to go only to the middle of the frame
    for (int i = 0; i < nEnd; i++) {
        int nNext = 0;
        if (i != 0) nNext = randint(-THICKNESS, THICKNESS);
        
        // identify positions
        int iRow = fIsVertical? i : iStartPosition;
        int iCol = fIsVertical? iStartPosition : i;

        if (!fIsAssym) { // if the image is symmetric then we should draw line from the both sides at the same time
            if (fIsVertical) drawLine(iCol, nSize - i - 1, BLACK, fIsVertical);
            else drawLine(nSize - i - 1, iRow, BLACK, fIsVertical);
        }
        
        drawLine(iCol, iRow, BLACK, fIsVertical);
        iStartPosition += nNext;
        
        // adjust the line so it will be only inside the frame
        if (iStartPosition + THICKNESS > nSize) iStartPosition -= THICKNESS;
        if (iStartPosition < 0) iStartPosition += THICKNESS;
    }   
}

void generateOutputName(char sOut[]) {
    SConfig* pConf = getConfig();
    strcpy(sOut, pConf->o != NULL? pConf->o : "");
    char* sRes = malloc(2 * sizeof(char*));

    switch (pConf->vhtype)
    {
        case vertical: 
            sRes[0] = 'v';
            break;
        case horizontal: 
            sRes[0] = 'h';
            break;
        default: 
            break;
    }

    switch (pConf->asstype)
    {
        case asymmetric: 
            sRes[1] = 'a';
            break;
        case symmetric: 
            sRes[1] = 's';
            break;
        default: 
            break;
    }
        
        
    char sSeed[MAX_FILENAME_SIZE];
    sprintf(sSeed, "%d", pConf->nSeed); // convert seed to string 
    strcat(sRes, sSeed); // add seed to the end of the file name

    strcat(sOut, sRes);
    strcat(sOut, ".bmp");
}