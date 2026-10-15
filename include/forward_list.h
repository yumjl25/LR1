#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

struct FNode{
    int data;
    FNode* next;
};

struct ForwardList{
    FNode* head;
    FNode* tail;
    int size;
};

void flistInit(ForwardList* list);
void flistFree(ForwardList* list);

bool flistIsEmpty(ForwardList* list);
int  flistLen(ForwardList* list);

void flistPushHead(ForwardList* list, int value);
void flistPushTail(ForwardList* list, int value);
void flistPushBefore(ForwardList* list, int target, int value);
void flistPushAfter(ForwardList* list, int target, int value);

int flistDelHead(ForwardList* list);
int flistDelTail(ForwardList* list);
int flistDelBefore(ForwardList* list, int target);
int flistDelAfter(ForwardList* list, int target);

bool flistDelValue(ForwardList* list, int value);
bool flistSearch(ForwardList* list, int value);

int  flistGetHead(ForwardList* list);
int  flistGetTail(ForwardList* list);
int  flistGetAt(ForwardList* list, int index);
void flistPrint(ForwardList* list);

#endif