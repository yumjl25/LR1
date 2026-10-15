#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <string>

struct FNode {
    std::string data;
    FNode* next;
};

struct ForwardList {
    FNode* head;
    FNode* tail;
    int size;
};

void flistInit(ForwardList* list);
void flistFree(ForwardList* list);
bool flistIsEmpty(ForwardList* list);

void flistPushHead(ForwardList* list, const std::string& value);
void flistPushTail(ForwardList* list, const std::string& value);
void flistPushBefore(ForwardList* list, const std::string& target, const std::string& value);
void flistPushAfter(ForwardList* list, const std::string& target, const std::string& value);

bool flistDelHead(ForwardList* list, std::string& out);
bool flistDelTail(ForwardList* list, std::string& out);
bool flistDelBefore(ForwardList* list, const std::string& target, std::string& out);
bool flistDelAfter(ForwardList* list, const std::string& target, std::string& out);
bool flistDelValue(ForwardList* list, const std::string& value);

bool flistSearch(ForwardList* list, const std::string& value);

bool flistGetHead(ForwardList* list, std::string& out);
bool flistGetTail(ForwardList* list, std::string& out);
bool flistGetAt(ForwardList* list, int index, std::string& out);

void flistPrint(ForwardList* list);

#endif