#include "mystr.h"
int mystrlen(char* str){
    int count;
    for (count = 0; str[count] != '\0'; count++);
    return count;
}
int charseek (const char *s, const char *accept)
{
    const char *a;
    for (a = accept; *a != '\0'; a++) if (*s == *a) return 1;
    return 0;
}
char* mystrdup(char *src)
{
    char *str;
    char *p;
    int len = 0;

    while (src[len])
        len++;
    str = malloc(len + 1);
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}

char* mystrtok(char* str, const char* delim){
    static char* buf = NULL;
    static int flag = 0;
    if (str != NULL) buf = str;
    if (flag    ) {flag = 0; return NULL;}
    str = buf;      
    int i = 0;
    for (i; charseek(&(buf)[i], delim); i++);
    int j = 0;
    buf += i;
    for (j; !charseek(&(buf)[j], delim) && (buf)[j] != '\0'; j++);
    if((buf)[j] == '\0'){
        flag = 1;
    }
    (buf)[j] = '\0';
    buf += (j+1);
    return buf-j-1;
}
char* mystrcat(char* dest, const char* src){
    char* ptr = dest + mystrlen(dest);
    while(*src != 0){
        *ptr++ = *src++;
    }
    *ptr = 0;
    return dest;
}
char* myreadline(const char* prompt){
    char *str = calloc(1, 1);
    char tmp[80];
    unsigned long long n = 0, len = 0;
    printf("%s",prompt);
    do {
        n = scanf("%79[^\n]", tmp);
        if (n == EOF) {free(str); str = NULL; return NULL;}
        if (n < 0){
            free(str);
            str = NULL;
            continue;
        }
        if (n == 0){
            scanf("%*c");
        } else {
            len += mystrlen(tmp);
            str = (char*)realloc(str, len+1);
            mystrcat(str, tmp);
        }
    } while (n > 0);    
    return str;
}