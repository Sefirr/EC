#ifndef _TRAFO_H
#define _TRAFO_H

#include "types.h"


void RGB2GrayMatrix(pixelRGB orig[], unsigned char dest[], int nfilas, int ncols);

void Gray2BinaryMatrix(unsigned char orig[], unsigned char dest[], unsigned char umbral, int nfilas, int ncols);

unsigned char rgb2gray(pixelRGB* pixel);

void Binary2BordeMatrix(unsigned char orig[], unsigned char dest[], int nfilas, int ncols);

#endif
