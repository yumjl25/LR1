#include <iostream>
#include "list.h"

using namespace std;

void listInit(List* list) {
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

void listFree(List* list) {
    LNode* cur = list->head;
    while (cur != nullptr) {
        LNode* next = cur->next;
        delete cur;
        cur = next;
    }
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

bool listIsEmpty(List* list) {
    return list->head == nullptr;
}


void listPushHead(List* list, int value) {
    LNode* node = new LNode{value, nullptr, list->head};
    if (list->head != nullptr) {
        list->head->prev = node;
    } else {
        list->tail = node;
    }
    list->head = node;
    list->size++;
}

void listPushTail(List* list, int value) {
    LNode* node = new LNode{value, list->tail, nullptr};
    if (list->tail != nullptr) {
        list->tail->next = node;
    } else {
        list->head = node;
    }
    list->tail = node;
    list->size++;
}

void listPushBefore(List* list, int target, int value) {
    LNode* cur = list->head;
    while (cur != nullptr && cur->data != target) {
        cur = cur->next;
    }
    if (cur == nullptr) {
        cout << "Target not found" << endl;
        return;
    }
    if (cur == list->head) {
        listPushHead(list, value);
        return;
    }
    LNode* node = new LNode{value, cur->prev, cur};
    cur->prev->next = node;
    cur->prev = node;
    list->size++;
}

void listPushAfter(List* list, int target, int value) {
    LNode* cur = list->head;
    while (cur != nullptr && cur->data != target) {
        cur = cur->next;
    }
    if (cur == nullptr) {
        cout << "Target not found" << endl;
        return;
    }
    // если target — хвост, вставляем в хвост
    if (cur == list->tail) {
        listPushTail(list, value);
        return;
    }
    LNode* node = new LNode{value, cur, cur->next};
    cur->next->prev = node;
    cur->next = node;
    list->size++;
}


int listDelHead(List* list) {
    if (listIsEmpty(list)) {
        cout << "List is empty" << endl;
        return -1;
    }
    LNode* old = list->head;
    int value = old->data;
    list->head = old->next;
    if (list->head != nullptr) {
        list->head->prev = nullptr;
    } else {
        list->tail = nullptr;
    }
    delete old;
    list->size--;
    return value;
}

int listDelTail(List* list) {
    if (listIsEmpty(list)) {
        cout << "List is empty" << endl;
        return -1;
    }
    LNode* old = list->tail;
    int value = old->data;
    list->tail = old->prev;
    if (list->tail != nullptr) {
        list->tail->next = nullptr;
    } else {
        list->head = nullptr;
    }
    delete old;
    list->size--;
    return value;
}

int listDelBefore(List* list, int target) {
    LNode* cur = list->head;
    while (cur != nullptr && cur->data != target) {
        cur = cur->next;
    }
    if (cur == nullptr || cur->prev == nullptr) {
        cout << "Nothing to delete before" << endl;
        return -1;
    }
    LNode* victim = cur->prev;
    int value = victim->data;
    cur->prev = victim->prev;
    if (victim->prev != nullptr) {
        victim->prev->next = cur;
    } else {
        list->head = cur;
    }
    delete victim;
    list->size--;
    return value;
}

int listDelAfter(List* list, int target) {
    LNode* cur = list->head;
    while (cur != nullptr && cur->data != target) {
        cur = cur->next;
    }
    if (cur == nullptr || cur->next == nullptr) {
        cout << "Nothing to delete after" << endl;
        return -1;
    }
    LNode* victim = cur->next;
    int value = victim->data;
    cur->next = victim->next;
    if (victim->next != nullptr) {
        victim->next->prev = cur;
    } else {
        list->tail = cur;
    }
    delete victim;
    list->size--;
    return value;
}


bool listDelValue(List* list, int value) {
    LNode* cur = list->head;
    while (cur != nullptr && cur->data != value) {
        cur = cur->next;
    }
    if (cur == nullptr) return false;

    if (cur->prev != nullptr) {
        cur->prev->next = cur->next;
    } else {
        list->head = cur->next;
    }
    if (cur->next != nullptr) {
        cur->next->prev = cur->prev;
    } else {
        list->tail = cur->prev;
    }
    delete cur;
    list->size--;
    return true;
}

bool listSearch(List* list, int value) {
    LNode* cur = list->head;
    while (cur != nullptr) {
        if (cur->data == value) return true;
        cur = cur->next;
    }
    return false;
}


int listGetHead(List* list) {
    if (listIsEmpty(list)) {
        cout << "List is empty" << endl;
        return -1;
    }
    return list->head->data;
}

int listGetTail(List* list) {
    if (listIsEmpty(list)) {
        cout << "List is empty" << endl;
        return -1;
    }
    return list->tail->data;
}

int listGetAt(List* list, int index) {
    if (index < 0 || index >= list->size) {
        cout << "Index out of range" << endl;
        return -1;
    }
    LNode* cur = list->head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    return cur->data;
}

void listPrint(List* list) {
    if (listIsEmpty(list)) {
        cout << "LIST: empty" << endl;
        return;
    }
    cout << "LIST:" << endl;
    LNode* cur = list->head;
    while (cur != nullptr) {
        cout << "  " << cur->data << endl;
        cur = cur->next;
    }
}