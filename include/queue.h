#ifndef QUEUE_H
#define QUEUE_H

#include <string>

struct QNode {
    std::string data;
    QNode* next;
};

struct Queue {
    QNode* head;
    QNode* tail;
};

void queueInit(Queue* q);
void queueFree(Queue* q);
bool queueIsEmpty(Queue* q);

void queuePush(Queue* q, const std::string& value);
bool queuePop(Queue* q, std::string& out);
bool queueGet(Queue* q, std::string& out);
void queuePrint(Queue* q);

#endif