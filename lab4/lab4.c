#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <stdio_ext.h>
#include <time.h>
#include "mystr.h"

#define _OPEN_SYS_UNLOCKED 1
#define DELIM " \t,."
#define PROMPT "> "

// Удалить первый символ каждого слова строки

char individual83(char**, char *);
char individual83_mine(char**, char *);

int main() {
    //printf("\033[H\033[2J");
    printf("Type your string\n");
    char *input = myreadline(PROMPT);
    double time = 0;
    while (input != NULL) {
        if (mystrlen(input) < 2) {input = myreadline(PROMPT); continue;}
        char *output = NULL;
        char *output2 = NULL;
        clock_t begin = clock();
        individual83(&output2, input);
        clock_t end = clock();
        double timetook1 = (double)(end-begin)/CLOCKS_PER_SEC;
        begin = clock();
        individual83_mine(&output, input);
        end = clock();
        printf("Output mine: %s\n", output);
        printf("Output C: %s\n", output2);
        printf("Time took C: %lf\n", timetook1);
        printf("Time took mine: %lf\n", (double)(end-begin)/CLOCKS_PER_SEC);
        free(input);
        free(output);
        free(output2);
        input = myreadline(PROMPT);
    }
    return 0;
}
char individual83(char** arr, char *str){
    char *s = strdup(str);
    int s_len = strlen(s);
    *arr = calloc(s_len + 1, sizeof(char));
    int len = 0;
    char *word = strtok(s, DELIM);
    while (word != NULL){
        len = strlen(word);
        word = strtok(NULL, DELIM);
    }
    int currpos = 0;
    free(s);
    s = strdup(str);
    word = strtok(s, DELIM);
    while (word != NULL){
        int curlen = strlen(word);
        if (curlen){
            if(curlen <= len){
                memcpy((*arr) + currpos, word, curlen * sizeof(char));
                currpos += curlen;
                (*arr)[currpos] = ' ';
                currpos += 1;
            }
            word = strtok(NULL, DELIM);
        }
        
    }
    (*arr)[currpos-1] = '\0';
    free(s);
}
char individual83_mine(char** arr, char *str){
    char *s = mystrdup(str);
    int s_len = mystrlen(s);
    if (*arr == NULL) *arr = calloc(s_len + 1, sizeof(char));
    else *arr = realloc(*arr, (s_len+1)*sizeof(char));
    int len = 0;

    fflush(stdout);
    char *word = mystrtok(s, DELIM);
    while (word != NULL){        
        len = strlen(word);
        word = mystrtok(NULL, DELIM);
    }
    int currpos = 0;
    free(s);
    free(word);
    s = mystrdup(str);
    fflush(stdout);
    word = mystrtok(s, DELIM);
    while (word != NULL){
        fflush(stdout);
        int curlen = mystrlen(word);
        if (curlen){
            if(curlen <= len){
                memcpy((*arr) + currpos, word, curlen * sizeof(char));
                currpos += curlen;
                (*arr)[currpos] = ' ';
                currpos += 1;
            }
            word = mystrtok(NULL, DELIM);
        }
        
    }
    (*arr)[currpos-1] = '\0';
    free(s);
}

