/*
 * Code réalisé pendant le semestre 3, réutilisé pour le projet
 */

#ifndef LINKED_LIST
#define LINKED_LIST



/* LISTES CHAINEES SIMPLES */

typedef struct ListNode ListNode;
struct ListNode{
    int data;
    ListNode* next;
};
typedef struct ListHead ListHead;
struct ListHead{
    ListNode* next;
    int length;
};

ListHead* ListInit();
void ListFree(ListHead* head);


void ListInsert(ListHead* head, int index, int data); // insert new element in at index
int ListPop(ListHead* head, int index);
void ListStack(ListHead* head, int X);
void ListQueue(ListHead* head, int X);

void ListPrint(ListHead* head);
int ListGetElement(ListHead* head, int index);
int ListFindElement(ListHead* head, int element);
void ListRemove(ListHead* head, int element);


// Special Functions
ListHead* ListFromArray(int* arr, int n);

bool ListContains(ListHead* head, int X);
void ListReverse(ListHead* head);

#endif