#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct SString{
    char* c;
    struct SString *next;
} SString;
typedef struct Queue{
    SString *head;
    SString *tail;
} Queue;
Queue *queue_new(){
    return (Queue*) calloc(1, sizeof(Queue));
}
void insertAfterWord(Queue *queue, char* str, const char* str2){
    SString* current = queue->head;
    while(current != NULL){
        if (!strcmp(current->c, str)){
            SString* new = calloc(1, sizeof(SString));
            new->c = strdup(str2);
            new->next = current->next;
            current->next = new;
            break;
        } else {
            current = current->next;
        }
    }
}
void doubleAllEven(Queue *queue){
    SString *current = queue->head;
    while (current != NULL) {
        if (strlen(current->c)%2==0){
            SString *new = calloc(1, sizeof(SString));
            new->c = strdup(current->c);
            new->next = current->next;
            current->next = new;
            current = current->next->next;
        } else {
            current = current->next;
        }
    }
}
void queue_delete_elements(Queue *queue, char *str) {
    if (queue->head == NULL) {
        printf("Queue is empty. Deletion failed.\n");
        return;
    }
    SString *current = queue->head;
    SString *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->c, str) == 0) {
            SString *temp = current;
            if (prev == NULL) {
                queue->head = current->next;
                if (queue->head == NULL) {
                    queue->tail = NULL;
                }
            } else {
                prev->next = current->next;
                if (prev->next == NULL) {
                    queue->tail = prev;
                }
            }
            current = current->next;
            free(temp->c); 
            free(temp);  
        } else {
            prev = current;
            current = current->next;
        }
    }
}
void queue_delete_word(Queue *queue, char* prompt){
    SString *ptr = queue->head, *ptr_prev = NULL;
    while(ptr){
        ptr_prev = ptr;
        ptr = ptr->next;
        if (!strcmp(prompt, ptr_prev->c)){
            free(ptr_prev->c);
            free(ptr_prev);
        }
    }
}
void queue_delete(Queue *queue){
    SString *ptr = queue->head, *ptr_prev = NULL;
    while(ptr){
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev->c);
        free(ptr_prev);
    }
    free(queue);
}

int queue_put(Queue *queue){
    SString *new = (SString*) calloc(1, sizeof(SString));
    if (!new) return 1;
    new->c = calloc(2, sizeof(char));
    new->next = NULL;
    if (!queue->head){
        queue->head = new;
        queue->tail = new;
    } else {
        queue->tail->next = new;
        queue->tail = new;
    }
    return 0;
}
void queue_update(Queue *queue, char data){
    int lencur = strlen(queue->tail->c);
    if (queue->tail->c == NULL) queue->tail->c = calloc(lencur+2, sizeof(char));
    else {
        queue->tail->c = realloc(queue->tail->c, lencur+2);
        queue->tail->c[lencur+1] = 0;
    }; 
    queue->tail->c[lencur] = data;
}

void queue_print(const Queue *queue) {
    SString *ptr = queue->head;
    while (ptr) {
        printf("%s ", ptr->c);
        ptr = ptr->next;
    }
    printf("\n");
}
int main(){
    char c;
    int len = 1;
    int flag = 0;
    int menu = 0;
    Queue *q = queue_new();
    while(1){
        printf("Choose:\n[1] Add to string\n[2] Insert after a word\n[3] Delete all elements with word\n[4] Double all even strings\n[5] Exit\n[1/2/3/4/5] ");
        if (!scanf("%d", &menu)) return 0;
        scanf("%*c");
        if (menu == 1){
            queue_put(q);
            while((c = getchar()) != '\n'){ 
                if (c == EOF) return 0;
                if (c == ' ' || c == '\t') {flag = 1; continue;}
                if (flag) { flag = 0; queue_put(q);}
                queue_update(q, c);
            }
            queue_print(q);
        }
        else if (menu == 2) {
            char* strin1 = calloc(1000, 1);
            char* strin2 = calloc(1000, 1);
            printf("Type which word to type after and word itself: ");
            if(!scanf("%s%s", strin1, strin2));
            insertAfterWord(q, strin1, strin2);
            queue_print(q);
            scanf("%*c");
            free(strin1);
            free(strin2);
        }
        else if (menu == 3) {
            char* strin = calloc(1000, 1);
            printf("Type which word to type after and word itself: ");
            if(!scanf("%s", strin)) return 0;
            queue_delete_elements(q, strin);
            queue_print(q);
            scanf("%*c");
            free(strin);
        }
        else if (menu == 4){
            doubleAllEven(q);
            queue_print(q);
        } else {
            queue_delete(q);
            return 0;
        }
    }
    queue_delete(q);


}
