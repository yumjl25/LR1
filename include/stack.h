#ifndef STACK_H
#define STACK_H

struct SNode{
    int data;
    SNode* next;
};

struct Stack{
    SNode* head;
};

void stackInit(Stack* s);
void stackFree(Stack* s);

bool stackISEmpty(Stack* s);

void stackPush(Stack* s, int value);
int stackPop(Stack* s);
int stackGet(Stack* s);

void stackPrint(Stack* s);

#endif