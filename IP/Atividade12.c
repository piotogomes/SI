#include <stdio.h>
#include <stdlib.h>


typedef struct s{
    int val;
    struct s* next;

} ListNode;

typedef struct{
    ListNode* start;
} List;

void inserir(List* l,int val) {
    ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->val = val;
    newNode->next = NULL;
    if (l->start == NULL) {
        l->start = newNode;
    }
    else {
        ListNode* aux = l->start;
        while(aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = newNode;
    }
}
void freeList(List* l) {
    ListNode* cur = l->start;
    while (cur != NULL){
        cur = cur->next;
        if(cur == NULL) {
            free(cur);
            cur = l->start;
        }
    }    
}

void DeleteNode(List* l, int val) {
    ListNode* cur = l->start;
    ListNode* aux = cur;
    while (cur != NULL){
        if(cur->val == val) {
            aux = cur->next;
            free(cur);
            l->start = aux;
            break;
        }
        cur = cur->next;
    }



}

void printList(List* l){
    ListNode* cur = l->start;
    while (cur != NULL){
        printf("%d -> ", cur->val);
        cur = cur->next;
    }
}


int main() {
    int n;
    List* l = (List*) calloc(1 ,sizeof(List));
    printf("Insira tamanho Lista: ");
    scanf("%d", &n);
    printf("Insira elementos ");
    for(int i = 0; i < n; i++){
        int val;
        scanf("%d", &val);
        inserir(l,val);
    }
    printList(l);
    DeleteNode(l, 3);
    printList(l);
    printf("\n");

    return 0;
}