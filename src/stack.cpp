#include <iostream>
#include "stack.h"

using namespace std;

void stackInit(Stack* s){
    s->head = nullptr;
}

void stackFree(Stack* s){
    SNode* cur = s->head;
    while(cur != nullptr){
        SNode* next = cur->next;
        delete cur;
        cur = next; 
    }
    s->head = nullptr;
}

bool stackIsEmpty(Stack* s){
    return s->head == nullptr;
}

void stackPush(Stack* s, int value){
    SNode* new_node = new SNode{value, s->head};
    s->head = new_node;
}

int stackPop(Stack* s){
    if (stackIsEmpty(s)){
        cout << "Stack is empty" << endl;
        return -1;
    }
    SNode* del_node = s->head;
    int value = del_node->data;
    s->head = del_node->next;
    delete del_node;
    return value;
}

int stackGet(Stack* s){
    if (stackIsEmpty(s)){
        cout << "Stack is empty" << endl;
        return -1;
    }
    return s->head->data;
}

void stackPrint(Stack* s){
    if (stackIsEmpty(s)){
        cout << "Stack is empty" << endl;
        return;
    }
    SNode* cur = s->head;
    while(cur != nullptr){
        cout << cur->data << endl;
        cur = cur->next;
    }
}