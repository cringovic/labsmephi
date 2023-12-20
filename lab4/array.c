#include <stdio.h>
#include <stdlib.h>
#include "array.h"
int init_arr(int arrsize, int **arr){
    *arr = (int*)calloc(arrsize, sizeof(int));
    if (arr == NULL) return 0;
    for (int i = 0; i < arrsize; i++){
        if (scanf("\n%d", &(*arr)[i]) == EOF) return 2;
    }
    return 1;
}

int insert(int** arr, int* arrsize, int* toinsert, int insize, int idx){
    if (idx > *arrsize) idx = *arrsize;
    *arrsize = *arrsize+insize;
    *arr = (int*)realloc(*arr, (*arrsize)*sizeof(int));
    if (arr == NULL) return 0;
    for (int i = *arrsize-1; i >= idx; i--){
        (*arr)[i] = (*arr)[i-insize];
        if (i-idx < insize) (*arr)[i] = toinsert[i-idx];
    }
    return 1;
}
int delete_idx(int** arr, int* arrsize, int idx, int num){
    if (idx > *arrsize) return 0;
    *arrsize = *arrsize-num;
    for (int i = idx; i < *arrsize; i++){
        (*arr)[i] = (*arr)[i+num];
    }
    *arr = realloc(*arr, (*arrsize)*sizeof(int));
    if (arr == NULL) return 0;
    return 1;
}
void print_arr(int* arr1, int arrsize){
    printf("\n");
    for (int i = 0; i < arrsize; i++){
        printf("%d ", arr1[i]);
    }
    printf("\n");
}