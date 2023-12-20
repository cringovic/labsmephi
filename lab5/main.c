#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <readline/readline.h>
typedef struct Cell
{
    char* fio;
    char ident[10];
    unsigned long timestamp;
} Cell;
void swap(void *a, void *b, size_t size) {
    void *tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
    return;
}
void equal(void *a, void *b, size_t size) {
    memcpy(a, b, size);
    return;
}
void insertion_sort(void* arr, int n, size_t size, int (*comparator)(const void*, const void*)){
    int i = 1, j;
    while (i < n){
        j = i - 1;
        void* temparr = malloc(size);
        memcpy(temparr, arr+i*size, size);
        while(j >= 0 && comparator(arr+j*size, temparr)){
            memcpy(arr+(j+1)*size, arr+j*size, size);
            j -= 1;
        }
        memcpy(arr+(j+1)*size, temparr, size);
        i += 1;
        free(temparr);
    }
}
void comb_sort(void* arr, int n, size_t size, int (*comparator)(const void*, const void*)){
	double factor = 1.247; 
	int step = n - 1; 
	while (step >= 1)
	{
		for (int i = 0; i + step < n; i++)
		{
			if (comparator(arr+i*size, arr+(i+step)*size))
			{
                swap(arr+i*size, arr+(i+step)*size, size);
			}
		}
		step /= factor;
	}   
}
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int is_higher (const void * a, const void * b) { 
    Cell *A = (Cell *)a;
    Cell *B = (Cell *)b;
    return (int*) A->timestamp < (int*) B->timestamp;
} 
int is_lower (const void * a, const void * b) { 
    Cell *A = (Cell *)a;
    Cell *B = (Cell *)b;
    return (int*) A->timestamp > (int*) B->timestamp;
} 
int fio_is_higher (const void * a, const void * b){
    Cell *A = (Cell *)a;
    Cell *B = (Cell *)b;
    if (strcmp( A->fio, B->fio) < 0) return 1;
    return 0;
}
int fio_is_lower (const void * a, const void * b){
    Cell *A = (Cell *)a;
    Cell *B = (Cell *)b;
    if (strcmp( A->fio, B->fio) > 0) return 1;
    return 0;
}
int ident_is_higher (const void * a, const void * b){
    Cell *A = (Cell *)a;
    Cell *B = (Cell *)b;
    if (strcmp( A->ident, B->ident) < 0) return 1;
    return 0;
}
int ident_is_lower (const void * a, const void * b){
    Cell *A = (Cell *)a;
    Cell *B = (Cell *)b;
    if (strcmp( A->ident, B->ident) > 0) return 1;
    return 0;
}
int mystrlen(char* str){
    int count;
    for (count = 0; str[count] != '\0'; count++);
    return count;
}

int main()
{
    Cell* ce = NULL; 
    int n = 0, p = 0, c = 0, d = 0;
    printf("\033[H\033[2J");
    printf("Choose 1 program or 2: [1/2] ");
    int res = scanf("%d", &n);
    printf("\033[H\033[2J");
    while (n==1) {
        printf("Choose:\n1: Enter data\n2: Print data\n3: Sort data\n4: Exit\n[1/2/3/4] ");
        if(scanf("%d", &p) == -1) break;
        printf("\n");
        while(p==1){
            printf("Choose:\n1: Using terminal\n2: Using txt\n3: Using binary\n4: Exit\n[1/2/3/4] ");
            if(scanf("%d", &c) == -1) break;
            if (c == 1){
                printf("\033[H\033[2J");
                printf("How many structures?\n");
                if(scanf("%d", &d) == -1) break;
                free(ce);
                ce = NULL;
                ce = calloc(d, sizeof(Cell));
                for (int i = 0; i < d; i++){
                    printf("%d\n", i+1);
                    printf("FIO:\n");
                    (ce+i)->fio=readline("");
                    if ((ce+i)->fio[mystrlen((ce+i)->fio)-1] == '\n') (ce+i)->fio[mystrlen((ce+i)->fio)-1] = 0;
                    printf("IDENT:\n");
                    scanf("%s", (ce+i)->ident);
                    printf("UNIX:\n");
                    scanf("%lu", &((ce+i)->timestamp));
                    (ce+i)->ident[9] = 0;
                }
            }
            if (c == 2){
                for (int i = 0; i < d; i++) free ((ce+i)->fio);
                FILE *fd = fopen("pseudosql.txt", "r");
                char* strtemp = calloc(1000, sizeof(char));
                fgets(strtemp, 999, fd);
                d = atoi((const char*) strtemp);
                printf("D %d\n", d);
                free(ce);
                ce = NULL;
                ce = calloc(d, sizeof(Cell));  
                free(strtemp);
                strtemp = NULL;  
                for (int i = 0; i < d; i++){
                    free((ce+i)->fio);
                    (ce+i)->fio = NULL;
                    (ce+i)->fio = calloc(1000, sizeof(char));
                    fgets((ce+i)->fio, 1000, fd);
                    if ((ce+i)->fio[mystrlen((ce+i)->fio)-1] == '\n') (ce+i)->fio[mystrlen((ce+i)->fio)-1] = 0;
                    fgets((ce+i)->ident, 11, fd);
                    strtemp = calloc(1000, sizeof(char));
                    fgets(strtemp, 999, fd);
                    (ce+i)->timestamp = atol(strtemp);
                    (ce+i)->ident[9] = 0;
                    free(strtemp);
                    strtemp = NULL;
                }
                fclose(fd);
            }
            if (c == 3){
                for (int i = 0; i < d; i++) free ((ce+i)->fio);
                FILE *fd = fopen("pseudosql", "rb");
                fread(&d, sizeof(int), 1, fd);
                printf("D %d\n", d);
                free(ce);
                ce = NULL;
                ce = calloc(d, sizeof(Cell)); 
                int quer = 0;   
                for (int i = 0; i < d; i++){
                    fread(&quer, sizeof(int), 1, fd);
                    free((ce+i)->fio);
                    (ce+i)->fio = NULL;
                    (ce+i)->fio = calloc(quer+1, sizeof(char));
                    fread((ce+i)->fio, quer, 1, fd);
                    fread((ce+i)->ident, 10*sizeof(char), 1, fd);
                    fread(&((ce+i)->timestamp), sizeof(unsigned long), 1, fd);
                    (ce+i)->ident[9] = 0;
                }
                fclose(fd);
            }
            if (c == 4){
                p = 0;
            }
            printf("\033[H\033[2J");
        }
        if (p == 2){
            printf("Choose:\n1: Using terminal\n2: Using txt\n3: Using binary\n4: Exit\n[1/2/3/4] ");
            if(scanf("%d", &c) == -1) break;
            if (d == 0){
                p = 0;
                continue;
            }
            if (c == 1){
                printf("\033[H\033[2J");
                for (int i = 0; i < d; i++){
                    printf("%d\n", i+1);
                    printf("FIO: %s\n", (ce+i)->fio);
                    printf("IDENT: %s\n", (ce+i)->ident);
                    printf("UNIX: %lu\n", (ce+i)->timestamp);
                }
            }
            if (c == 2){
                FILE *fd = fopen("pseudosql.txt", "w");
                fprintf(fd, "%d\n", d);
                for (int i = 0; i < d; i++){
                    fprintf(fd, "%s\n", (ce+i)->fio);
                    fprintf(fd, "%s\n", (ce+i)->ident);
                    fprintf(fd, "%lu\n", (ce+i)->timestamp);
                }
                printf("\033[H\033[2J");
                fclose(fd);
            }
            if (c == 3){
                FILE *fd = fopen("pseudosql", "wb");
                fwrite(&d, sizeof(int), 1, fd);
                for (int i = 0; i < d; i++){
                    int quer = mystrlen((ce+i)->fio);
                    fwrite(&quer, sizeof(int), 1, fd);
                    fwrite((ce+i)->fio, quer, 1, fd);
                    fwrite((ce+i)->ident, 10, 1, fd);
                    fwrite(&((ce+i)->timestamp), sizeof(unsigned long), 1, fd);
                }
                fclose(fd);
                printf("\033[H\033[2J");
            }            
            if (c == 4){
                p = 0;
                printf("\033[H\033[2J");
            }
            
        }
        if (p == 3){
            int g = 0, e = 0, f = 0;
            printf("\033[H\033[2J");
            printf("Choose sort algorythm\n1. Quick sort\n2. Comb sort\n3. Insertion sort\nExit\n[1/2/3/4] ");
            if(scanf("%d", &g) == -1) break;
            if (g == 4) {
                p = 0;
                continue;
            }
            printf("\033[H\033[2J");
            printf("\nWhich row? (4 for exit): [1/2/3/4] ");
            if(scanf("%d", &e) == -1) break;
            if (e == 4) {
                p = 0;
                continue;
            }
            printf("\033[H\033[2J");
            printf("\nNon-descending/Descending: [1/2/4] ");
            if(scanf("%d", &f) == -1) break;
            if (f == 4 || f == 3) {
                p = 0;
                continue;
            }
            if (g == 1){
                printf("D %d\n", d);
                if (e == 1){
                    if (f == 1) qsort(ce, d, sizeof(Cell), fio_is_lower);
                    if (f == 2) qsort(ce, d, sizeof(Cell), fio_is_higher);
                }
                if (e == 2){
                    if (f == 1) qsort(ce, d, sizeof(Cell), ident_is_lower);
                    if (f == 2) qsort(ce, d, sizeof(Cell), ident_is_higher);
                }
                if (e == 3){
                    if (f == 1) qsort(ce, d, sizeof(Cell), is_lower);
                    if (f == 2) qsort(ce, d, sizeof(Cell), is_higher);
                }
                printf("D %d\n", d);
            }
            if (g == 2){
                if (e == 1){
                    if (f == 1) comb_sort(ce, d, sizeof(Cell), fio_is_lower);
                    if (f == 2) comb_sort(ce, d, sizeof(Cell), fio_is_higher);
                }
                if (e == 2){
                    if (f == 1) comb_sort(ce, d, sizeof(Cell), ident_is_lower);
                    if (f == 2) comb_sort(ce, d, sizeof(Cell), ident_is_higher);
                }
                if (e == 3){
                    if (f == 1) comb_sort(ce, d, sizeof(Cell), is_lower);
                    if (f == 2) comb_sort(ce, d, sizeof(Cell), is_higher);
                }
            }
            if (g == 3){
                if (e == 1){
                    if (f == 1) insertion_sort(ce, d, sizeof(Cell), fio_is_lower);
                    if (f == 2) insertion_sort(ce, d, sizeof(Cell), fio_is_higher);
                }
                if (e == 2){
                    if (f == 1) insertion_sort(ce, d, sizeof(Cell), ident_is_lower);
                    if (f == 2) insertion_sort(ce, d, sizeof(Cell), ident_is_higher);
                }
                if (e == 3){
                    if (f == 1) insertion_sort(ce, d, sizeof(Cell), is_lower);
                    if (f == 2) insertion_sort(ce, d, sizeof(Cell), is_higher);
                }
            }
            printf("\033[H\033[2J");
        }
        if (p == 4){
            n = 0;
        }
    } 
    while (n == 2){
        int num = 0;
        int z = 0;
        printf("\033[H\033[2J");
        printf("Number of elements \n");
        if (scanf("%d", &num) == -1) break;
        Cell *ce = NULL;
        ce = calloc(num, sizeof(Cell));
        for (int i = 0; i < num; i++){
            (ce+i)->timestamp = rand();
            for (int j = 0; j < 9; j++) (ce+i)->ident[j] = 'A'+(rand()%26);
            int strln = rand() % 999;
            (ce+i)->fio = calloc(strln+1, sizeof(char));
            for (int j = 0; j < strln - 1; j++) (ce+i)->fio[j] = 'A'+(rand()%26);
            (ce+i)->fio[strln] = 0;
        }
        z = 1;
        while (z == 1){
            int g = 0, e = 0, f = 0;
            printf("Choose sort algorythm\n1. Quick sort\n2. Comb sort\n3. Insertion sort\nExit\n[1/2/3/4] ");
            if(scanf("%d", &g) == -1) break;
            if (g == 4) {
                z = 0;
                continue;
            }
            printf("\033[H\033[2J");
            printf("\nWhich row? (4 for exit): [1/2/3/4] ");
            if(scanf("%d", &e) == -1) break;
            if (e == 4) {
                z = 0;
                continue;
            }
            printf("\033[H\033[2J");
            printf("\nNon-descending/Descending: [1/2/4] ");
            if(scanf("%d", &f) == -1) break;
            if (f == 4 || f == 3) {
                z = 0;
                continue;
            }
            clock_t begin, end;
            if (g == 1){
                if (e == 1){
                    if (f == 1) {begin = clock(); qsort(ce, num, sizeof(Cell), fio_is_lower); end = clock();}
                    if (f == 2) {begin = clock(); qsort(ce, num, sizeof(Cell), fio_is_higher); end = clock();}
                }
                if (e == 2){
                    if (f == 1) {begin = clock(); qsort(ce, num, sizeof(Cell), ident_is_lower); end = clock();}
                    if (f == 2) {begin = clock(); qsort(ce, num, sizeof(Cell), ident_is_higher); end = clock();}
                }
                if (e == 3){
                    if (f == 1) {begin = clock(); qsort(ce, num, sizeof(Cell), is_lower); end = clock();}
                    if (f == 2) {begin = clock(); qsort(ce, num, sizeof(Cell), is_higher); end = clock();}
                }
            }
            if (g == 2){
                if (e == 1){
                    if (f == 1) {begin = clock(); comb_sort(ce, num, sizeof(Cell), fio_is_lower); end = clock();}
                    if (f == 2) {begin = clock(); comb_sort(ce, num, sizeof(Cell), fio_is_higher); end = clock();}
                }
                if (e == 2){
                    if (f == 1) {begin = clock(); comb_sort(ce, num, sizeof(Cell), ident_is_lower); end = clock();}
                    if (f == 2) {begin = clock(); comb_sort(ce, num, sizeof(Cell), ident_is_higher); end = clock();}
                }
                if (e == 3){
                    if (f == 1) {begin = clock(); comb_sort(ce, num, sizeof(Cell), is_lower); end = clock();}
                    if (f == 2) {begin = clock(); comb_sort(ce, num, sizeof(Cell), is_higher); end = clock();}
                }
            }
            if (g == 3){
                if (e == 1){
                    if (f == 1) {begin = clock(); insertion_sort(ce, num, sizeof(Cell), fio_is_lower); end = clock();}
                    if (f == 2) {begin = clock(); insertion_sort(ce, num, sizeof(Cell), fio_is_higher); end = clock();}
                }
                if (e == 2){
                    if (f == 1) {begin = clock(); insertion_sort(ce, num, sizeof(Cell), ident_is_lower); end = clock();}
                    if (f == 2) {begin = clock(); insertion_sort(ce, num, sizeof(Cell), ident_is_higher); end = clock();}
                }
                if (e == 3){
                    if (f == 1) {begin = clock(); insertion_sort(ce, num, sizeof(Cell), is_lower); end = clock();}
                    if (f == 2) {begin = clock(); insertion_sort(ce, num, sizeof(Cell), is_higher); end = clock();}
                }
            }
            printf("\033[H\033[2J");
            printf("Time took: %lf\n", (double)(end-begin)/CLOCKS_PER_SEC);
        }
        for (int i = 0; i < num; i++) free ((ce+i)->fio);
        free(ce);
    }
    for (int i = 0; i < d; i++) free ((ce+i)->fio);
    free(ce);
    return 0;

}