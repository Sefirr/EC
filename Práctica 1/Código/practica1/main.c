#include <stdio.h>
#include "trafo.h"
#include "types.h"

#define N 8
#define M 4


#define FACTOR ( (unsigned char) ( 255/(N+M-2) ) )

extern void contarUnos(unsigned char mat[], short int vector[],int nfilas, int ncols);



pixelRGB imagenRGB[N*M];
unsigned char imagenGris[N*M];
unsigned char imagenBinaria[N*M];
unsigned char imagenBorde[N*M];
short int unosPorFila[N];

void initRGB(pixelRGB m[], int nfilas, int ncols) {

    int i,j;
    
    for (i=0;i<nfilas;i++)
        for (j=0; j<ncols; j++) {
            m[i*ncols+j].R = (i+j)*FACTOR;
            m[i*ncols+j].G = (i+j)*FACTOR;
            m[i*ncols+j].B = (i+j)*FACTOR;
        }
}



int main() {
    
    initRGB(imagenRGB,N,M);
    RGB2GrayMatrix(imagenRGB,imagenGris,N,M);
    Gray2BinaryMatrix(imagenGris,imagenBinaria,127,N,M);
    contarUnos(imagenBinaria,unosPorFila,N,M);
    Binary2BordeMatrix(imagenBinaria, imagenBorde, N, M);
    return 0;
}
