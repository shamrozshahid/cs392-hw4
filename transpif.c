#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char **argv) {

    int matrixH = atoi(argv[1]);
    int matrixW = atoi(argv[2]);
    int blockW = atoi(argv[3]);
    int matrixSize = matrixH * matrixW;

    float *inputMatrix = malloc(matrixSize * sizeof(float));
    float *transpMatrix = malloc(matrixSize * sizeof(float));

    time_t t;
    srand(time(&t));
    for (int i = 0; i < matrixSize; i++){
        inputMatrix[i] = rand();
    }
/*

    int row = 0;
    for (int i = 0; i < matrixSize; i += matrixW){
        printf("row %d : ", row);
        row++;
        for (int j = i; j < matrixW + i; j++){
            printf("%f ", inputMatrix[j]);
        }
        printf("\n");
    }

*/
    struct timeval start;
    struct timeval end;
    gettimeofday(&start, 0);
    int blockHeight = blockW;
    int blockWidth = blockW;
    for(int i = 0; i < matrixW; i += blockW){
        for(int j = 0; j < matrixH; j += blockW){

            if(blockWidth+i > matrixW){
                blockWidth = matrixW;
            }
            else{
                blockWidth = blockWidth +i;
            }

            for(int k = i; k < blockWidth; k++){

                if (blockHeight + j > matrixH){
                    blockHeight = matrixH;
                }
                else{
                    blockHeight = blockHeight + j;
                }

                for(int l = j; l < blockHeight; l++){
                    transpMatrix[l + k * matrixH] = inputMatrix[l * matrixW + k];
                }
            }
        }
    }
    gettimeofday(&end, 0);
    long long elapsed = (end.tv_sec-start.tv_sec)*1000000LL + end.tv_usec-start.tv_usec;

/*
    row = 0;
    printf("------------Transposed Matrix---------- \n");
    for (int i = 0; i < matrixSize; i += matrixH){
        printf("row %d : ", row);
        row++;
        for (int j = i; j < matrixH + i; j++){
            printf("%f ", transpMatrix[j]);
        }
        printf("\n");
    }

*/
    free(inputMatrix);
    free(transpMatrix);
    printf("Time: %lld \n",elapsed);


    return 0;
}