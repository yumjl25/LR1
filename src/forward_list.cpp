#include <iostream>
#include "forward_list.h"

using namespace std;

void flistInit(ForwardList* list){
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

void flistFree(ForwardList* list){
    FNode* cur = list->head;
    while(cur != nullptr){
        FNode* next = cur->next;
        delete cur;
        cur = next;
    }
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
}

bool flistIsEmpty(ForwardList* list){
    return list->head == nullptr;
}


void flistPushHead(ForwardList* list, int value){
    FNode* new_node = new FNode{value, list->head};
    list->head = new_node;
    if (list->tail == nullptr){
        list->tail = new_node;
    }
    list->size++;
}

void flistPushTail(ForwardList* list, int value){
    FNode* new_node = new FNode{value, nullptr};
    if (list->tail == nullptr){
        list->head = new_node;
        list->tail = new_node;
    }else{
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
}

void flistPushBefore(ForwardList* list, int target, int value){
    if (list->head == nullptr){return;}

    if (list->head->data == target){
        flistPushHead(list, value);
        return;
    }

    FNode* cur = list->head;
    while(cur->next != nullptr && cur->next->data != target){
        cur = cur->next;
    }
    if (cur->next == nullptr){
        cout << "Target not found" << endl;
        return;
    }

    FNode* new_node = new FNode{value, cur->next};
    cur->next = new_node;
    list->size++;
}

void flistPushAfter(ForwardList* list, int target, int value){
    FNode* cur = list->head;
    while (cur != nullptr && cur->data != target){
        cur = cur->next;
    }
    if(cur == nullptr){
        cout << "Target not found" << endl;
        return;
    }
    FNode* new_node = new FNode{value, cur->next};
    cur->next = new_node;
    if (cur == list->tail){
        list->tail = new_node;
    }
    list->size++;
}

int flistDelHead(ForwardList* list){
    if (flistIsEmpty(list)){
        cout << "Forward list is empty" << endl;
        return -1;
    }
    FNode* del_node = list->head;
    int value = del_node->data;
    list->head = del_node->next;
    if (list->head == nullptr){
        list->tail = nullptr;
    }
    delete del_node;
    list->size--;
    return value;
}

int flistDelTail(ForwardList* list){
    if (flistIsEmpty(list)){
        cout << "Forward list is empty" << endl;
        return -1;
    }
    if (list->head == list->tail){
        return flistDelHead(list);
    }
    FNode* cur = list->head;
    while (cur->next != list->tail){
        cur = cur->next;
    }
    int value = list->tail->data;
    delete list->tail;
    list->tail = cur;
    cur->next = nullptr;
    list->size--;
    return value;
}

int flistDelBefore(ForwardList* list, int target){
    if (flistIsEmpty(list) || list->head->data == target){
        cout << "Nothing to delete before" << endl;
        return -1;
    }
    FNode* prev = nullptr;
    FNode* cur = list->head;
    while (cur != nullptr && cur->data != target) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == nullptr || prev == nullptr) {
        cout << "Target not found" << endl;
        return -1;
    }
    if (prev == list->head) {
        return flistDelHead(list);
    }
    FNode* before_prev = list->head;
    while (before_prev->next != prev) {
        before_prev = before_prev->next;
    }
    int value = prev->data;
    before_prev->next = cur;
    delete prev;
    list->size--;
    return value;
}

int flistDelAfter(ForwardList* list, int target) {
    FNode* cur = list->head;
    while (cur != nullptr && cur->data != target) {
        cur = cur->next;
    }
    if (cur == nullptr || cur->next == nullptr) {
        cout << "Nothing to delete after" << endl;
        return -1;
    }
    FNode* del_node = cur->next;
    int value = del_node->data;
    cur->next = del_node->next;
    if (del_node == list->tail) {
        list->tail = cur;
    }
    delete del_node;
    list->size--;
    return value;
}

bool flistDelValue(ForwardList* list, int value) {
    if (flistIsEmpty(list)) return false;

    if (list->head->data == value) {
        flistDelHead(list);
        return true;
    }

    FNode* cur = list->head;
    while (cur->next != nullptr && cur->next->data != value) {
        cur = cur->next;
    }
    if (cur->next == nullptr) return false;

    FNode* del_node = cur->next;
    cur->next = del_node->next;
    if (del_node == list->tail) {
        list->tail = cur;
    }
    delete del_node;
    list->size--;
    return true;
}

bool flistSearch(ForwardList* list, int value) {
    FNode* cur = list->head;
    while (cur != nullptr) {
        if (cur->data == value) return true;
        cur = cur->next;
    }
    return false;
}

int flistGetHead(ForwardList* list) {
    if (flistIsEmpty(list)) {
        cout << "List is empty" << endl;
        return -1;
    }
    return list->head->data;
}

int flistGetTail(ForwardList* list) {
    if (flistIsEmpty(list)) {
        cout << "List is empty" << endl;
        return -1;
    }
    return list->tail->data;
}

int flistGetAt(ForwardList* list, int index) {
    if (index < 0 || index >= list->size) {
        cout << "Index out of range" << endl;
        return -1;
    }
    FNode* cur = list->head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    return cur->data;
}

void flistPrint(ForwardList* list) {
    if (flistIsEmpty(list)) {
        cout << "LIST: empty" << endl;
        return;
    }
    cout << "LIST:" << endl;
    FNode* cur = list->head;
    while (cur != nullptr) {
        cout << "  " << cur->data << endl;
        cur = cur->next;
    }
}