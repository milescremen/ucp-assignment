

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
/* Includes */
#include <stdlib.h>
#include <stdio.h>


typedef void (*Print)(void*);
typedef void (*Free)(void*);
typedef void(*Output)(void*, FILE* f);

/* Typedef's */
typedef struct ListNode {
    void* data;
    struct ListNode* next;
    struct ListNode* prev;
} Node;

typedef struct LinkedList {
    struct ListNode* head;
    struct ListNode* tail;
    int size;
    Print printFunc;
    Free freeFunc;
    Output outputFunc;
} LinkedList;



/* Forward declaration */

LinkedList* createLinkedList(Print print, Free free, Output output);
void insertFirst(void* inData, LinkedList* list);
void insertLast(void* inData, LinkedList* list);
void* removeFirst(LinkedList* list);
void* removeLast(LinkedList* list);
void printLinkedList(LinkedList* list);
void freeLinkedList(LinkedList* list);

void logsPrinter(void* ptr);
void logsFree(void* ptr);
void logsFileFunc(void* ptr, FILE* f);
#endif