/*
 * Code réalisé pendant le semestre 3, réutilisé pour le projet
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "linked_list.h"

/* LISTES CHAINEES SIMPLES */

ListHead* ListInit() {
    ListHead* new = malloc(1*sizeof(ListHead));
    new->length = 0;
    new->next = NULL;
    return new;
}
void ListFree(ListHead* head) {
    while (head->length > 0) {
        ListPop(head, 0);
    }
    free(head);
}

void ListInsert(ListHead* head, int index, int data) {
    if (index > head->length) {
        printf("Cant insert data %d at index %d : List too short", data, index);
        exit(-1);
    }

    ListNode* new = malloc(1*sizeof(ListNode));
    new->data = data;
    new->next = NULL;
    head->length++;

    if (index == 0) {
        new->next = head->next;
        head->next = new;
        return;
    }

    ListNode* ptr = head->next;
    index--;
    while (index > 0){
        ptr = ptr->next;
        index--;
    }
    new->next = ptr->next;
    ptr->next = new;

}
int ListPop(ListHead* head, int index) {
    if (head->length <= index) {
        printf("Can't Pop non existing element");
        exit(-1);
    }
    head->length--;
    ListNode* temp;
    int val;

    if (index == 0) {
        val = head->next->data;
        temp = head->next->next;
        free(head->next);
        head->next = temp;
        return val;
    }

    ListNode* ptr = head->next;
    index--;
    while (index > 0) {
        ptr = ptr->next;
        index--;
    }

    temp = ptr->next;
    ptr->next = temp->next;
    val = temp->data;
    free(ptr->next);
    return val;
}
void ListStack(ListHead* head, int X) {
    ListInsert(head, 0, X);
}
void ListQueue(ListHead* head, int X) {
    ListInsert(head, head->length, X);
}

void ListPrint(ListHead* head) {
    ListNode* ptr = head->next;
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}
int ListGetElement(ListHead* head, int index) {
    if (index >= head->length) {
        printf("Cannot reach index %d: out of bounds", index);
        exit(-1);
    }
    ListNode* ptr = head->next;
    while (index > 0) {
        ptr = ptr->next;
        index --;
    }
    return ptr->data;
}



// Special Functions
ListHead* ListFromArray(int* arr, int n) {
    if (n == 0) {
        return ListInit();
    }
    ListHead* new = malloc(1*sizeof(ListHead));
    new->length = n;
    new->next = malloc(1*sizeof(ListNode));
    ListNode* ptr = new->next;
    ptr->data = arr[0];
    ptr->next = NULL;
    for (int i = 1; i < n; i++) {
        ptr->next = malloc(1*sizeof(ListNode));
        ptr = ptr->next;
        ptr->data = arr[i];
    }
    ptr->next = NULL;

    return new;
}

bool ListContains(ListHead* head, int X) {
    ListNode* ptr = head->next;

    while (ptr != NULL) {
        if (ptr->data == X) {
            return true;
        }
        ptr = ptr->next;
    }

    return false;
}

void ListReverse(ListHead* head) {
    ListNode* ptr = head->next;
    ListNode* ptr2 = ptr->next;
    ListNode* temp;
    ptr->next = NULL;
    while (ptr2 != NULL) {
        temp = ptr2->next;
        ptr2->next = ptr;
        ptr = ptr2;
        ptr2 = temp;
    }
    head->next = ptr;
}