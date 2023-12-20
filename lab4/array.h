#ifndef ARRAY_H
#define ARRAY_H
int init_arr(int arrsize, int **arr);
int insert(int** arr, int* arrsize, int* toinsert, int insize, int idx);
int delete_idx(int** arr, int* arrsize, int idx, int num);
void print_arr(int* arr1, int arrsize);
#endif