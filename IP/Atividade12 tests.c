#include <stdio.h>
#include <stdlib.h>


typedef struct s{
    int val;
    struct s* next;

} ListNode;


void inserir(ListNode* start,int val) {
    ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->val = val;
    newNode->next = NULL;
    if (start == NULL) {
        start = newNode;
    }
    else {
        ListNode* aux = start;
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}


void printList(ListNode* start){
    ListNode* cur = start;
    while (cur != NULL){
        printf("%d -> ", cur->val);
        cur = cur->next;
    }
}

void freeList(ListNode* start) {
    ListNode* cur = start;
    while (cur->next != NULL){
        cur = cur->next;
        if(cur == NULL) {
            free(cur);
            cur = start;
        }
    }    
}

int main() {
    int n;
    ListNode* start = (ListNode*) malloc(sizeof(ListNode));   
    printf("Insira tamanho Lista: ");
    scanf("%d", &n);
    printf("Insira elementos ");
    for(int i = 0; i < n; i++){
        int val;
        scanf("%d", &val);
        inserir(start,val);
    }
    printList(start);
    printf("\n");

    freeList(start);

    return 0;
}