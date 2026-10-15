#ifndef STORAGE_H
#define STORAGE_H

#include "array.h"
#include "forward_list.h"
#include "list.h"
#include "stack.h"
#include "queue.h"
#include "avl.h"

struct ArrayEntry {
    char* name;
    Array* array;
    ArrayEntry* next;
};

struct FListEntry {
    char* name;
    ForwardList* list;
    FListEntry* next;
};

struct ListEntry {
    char* name;
    List* list;
    ListEntry* next;
};

struct StackEntry {
    char* name;
    Stack* stack;
    StackEntry* next;
};

struct QueueEntry {
    char* name;
    Queue* queue;
    QueueEntry* next;
};

struct TreeEntry {
    char* name;
    AVLTree* tree;
    TreeEntry* next;
};

struct Storage {
    ArrayEntry* arrays;
    FListEntry* flists;
    ListEntry*  lists;
    StackEntry* stacks;
    QueueEntry* queues;
    TreeEntry*  trees;
};

Storage* storageCreate();
void     storageFree(Storage* s);

Array*       storageGetArray(Storage* s, const char* name);
ForwardList* storageGetFList(Storage* s, const char* name);
List*        storageGetList(Storage* s, const char* name);
Stack*       storageGetStack(Storage* s, const char* name);
Queue*       storageGetQueue(Storage* s, const char* name);
AVLTree*     storageGetTree(Storage* s, const char* name);

void storageExecute(Storage* s, const char* query, bool quiet);
void storageLoad(Storage* s, const char* filename);
void storageSave(Storage* s, const char* filename);

#endif