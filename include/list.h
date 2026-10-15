#ifndef LIST_H
#define LIST_H

struct LNode {
    int data;
    LNode* prev;
    LNode* next;
};

struct List {
    LNode* head;
    LNode* tail;
    int size;
};

void listInit(List* list);
void listFree(List* list);

bool listIsEmpty(List* list);
int  listLen(List* list);

void listPushHead(List* list, int value);
void listPushTail(List* list, int value);
void listPushBefore(List* list, int target, int value);
void listPushAfter(List* list, int target, int value);

int listDelHead(List* list);
int listDelTail(List* list);
int listDelBefore(List* list, int target);
int listDelAfter(List* list, int target);

bool listDelValue(List* list, int value);
bool listSearch(List* list, int value);

int  listGetHead(List* list);
int  listGetTail(List* list);
int  listGetAt(List* list, int index);
void listPrint(List* list);

#endif