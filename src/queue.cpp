#include <iostream>
#include "queue.h"

using namespace std;

void queueInit(Queue* q){
    q->head = nullptr;
    q->tail = nullptr;
}

void queueFree(Queue* q){
    QNode* cur = q->head;
    while (cur != nullptr){
        QNode* next = cur->next;
        delete cur;
        cur = next;
    }
    q->head = nullptr;
    q->tail = nullptr;
}

bool queueIsEmpty(Queue* q){
    return q->head == nullptr;
}

void queuePush(Queue* q, int value){
    QNode* new_node = new QNode{value, nullptr};
    if (queueIsEmpty(q)){
        q->head = new_node;
        q->tail = new_node;
    }else{
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

int queuePop(Queue* q){
    if(queueIsEmpty(q)){
        cout << "Queue is empty" << endl;
        return -1;
    }
    QNode* del_node = q->head;
    int value = del_node->data;
    q->head = del_node->next;
    if(q->head == nullptr){
        q->tail = nullptr;
    }
    delete del_node;
    return value;
}

int queueGet(Queue* q){
    if (queueIsEmpty(q)){
        cout << "Queue is empty" << endl;
        return -1;
    }
    return q->head->data;
}

void queuePrint(Queue* q){
    if (queueIsEmpty(q)){
        cout << "Queue is empty" << endl;
        return;
    }
    QNode* cur = q->head;
    while(cur != nullptr){
        cout << cur->data << endl;
        cur = cur->next;
    }
}