#ifndef QUEUE_H
#define QUEUE_H

struct QNode{
    int data;
    QNode* next;
};

struct Queue{
    QNode* head;
    QNode* tail;
};

void queueInit(Queue* q);
void queueFree(Queue* q);

bool queueIsEmpty(Queue* q);

void queuePush(Queue* q, int value);
int queuePop(Queue* q);
int queueGet(Queue* q);

void queuePrint(Queue* q);

#endif