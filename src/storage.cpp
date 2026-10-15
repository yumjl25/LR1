#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "storage.h"

using namespace std;

static char* myStrdup(const char* src) {
    int len = strlen(src);
    char* dst = new char[len + 1];
    strcpy(dst, src);
    return dst;
}

Storage* storageCreate() {
    Storage* s = new Storage;
    s->arrays = nullptr;
    s->flists = nullptr;
    s->lists  = nullptr;
    s->stacks = nullptr;
    s->queues = nullptr;
    s->trees  = nullptr;
    return s;
}

void storageFree(Storage* s) {
    ArrayEntry* a = s->arrays;
    while (a) {
        ArrayEntry* next = a->next;
        arrayFree(a->array);
        delete a->array;
        delete[] a->name;
        delete a;
        a = next;
    }
    FListEntry* f = s->flists;
    while (f) {
        FListEntry* next = f->next;
        flistFree(f->list);
        delete f->list;
        delete[] f->name;
        delete f;
        f = next;
    }
    ListEntry* l = s->lists;
    while (l) {
        ListEntry* next = l->next;
        listFree(l->list);
        delete l->list;
        delete[] l->name;
        delete l;
        l = next;
    }
    StackEntry* st = s->stacks;
    while (st) {
        StackEntry* next = st->next;
        stackFree(st->stack);
        delete st->stack;
        delete[] st->name;
        delete st;
        st = next;
    }
    QueueEntry* q = s->queues;
    while (q) {
        QueueEntry* next = q->next;
        queueFree(q->queue);
        delete q->queue;
        delete[] q->name;
        delete q;
        q = next;
    }
    TreeEntry* t = s->trees;
    while (t) {
        TreeEntry* next = t->next;
        avlFree(t->tree);
        delete t->tree;
        delete[] t->name;
        delete t;
        t = next;
    }
    delete s;
}

Array* storageGetArray(Storage* s, const char* name) {
    ArrayEntry* cur = s->arrays;
    while (cur) {
        if (strcmp(cur->name, name) == 0) return cur->array;
        cur = cur->next;
    }
    ArrayEntry* entry = new ArrayEntry;
    entry->name = myStrdup(name);
    entry->array = new Array;
    arrayInit(entry->array);
    entry->next = s->arrays;
    s->arrays = entry;
    return entry->array;
}

ForwardList* storageGetFList(Storage* s, const char* name) {
    FListEntry* cur = s->flists;
    while (cur) {
        if (strcmp(cur->name, name) == 0) return cur->list;
        cur = cur->next;
    }
    FListEntry* entry = new FListEntry;
    entry->name = myStrdup(name);
    entry->list = new ForwardList;
    flistInit(entry->list);
    entry->next = s->flists;
    s->flists = entry;
    return entry->list;
}

List* storageGetList(Storage* s, const char* name) {
    ListEntry* cur = s->lists;
    while (cur) {
        if (strcmp(cur->name, name) == 0) return cur->list;
        cur = cur->next;
    }
    ListEntry* entry = new ListEntry;
    entry->name = myStrdup(name);
    entry->list = new List;
    listInit(entry->list);
    entry->next = s->lists;
    s->lists = entry;
    return entry->list;
}

Stack* storageGetStack(Storage* s, const char* name) {
    StackEntry* cur = s->stacks;
    while (cur) {
        if (strcmp(cur->name, name) == 0) return cur->stack;
        cur = cur->next;
    }
    StackEntry* entry = new StackEntry;
    entry->name = myStrdup(name);
    entry->stack = new Stack;
    stackInit(entry->stack);
    entry->next = s->stacks;
    s->stacks = entry;
    return entry->stack;
}

Queue* storageGetQueue(Storage* s, const char* name) {
    QueueEntry* cur = s->queues;
    while (cur) {
        if (strcmp(cur->name, name) == 0) return cur->queue;
        cur = cur->next;
    }
    QueueEntry* entry = new QueueEntry;
    entry->name = myStrdup(name);
    entry->queue = new Queue;
    queueInit(entry->queue);
    entry->next = s->queues;
    s->queues = entry;
    return entry->queue;
}

AVLTree* storageGetTree(Storage* s, const char* name) {
    TreeEntry* cur = s->trees;
    while (cur) {
        if (strcmp(cur->name, name) == 0) return cur->tree;
        cur = cur->next;
    }
    TreeEntry* entry = new TreeEntry;
    entry->name = myStrdup(name);
    entry->tree = new AVLTree;
    avlInit(entry->tree);
    entry->next = s->trees;
    s->trees = entry;
    return entry->tree;
}

void storageExecute(Storage* s, const char* query, bool quiet) {
    char tokens[10][64];
    int n = 0;
    int i = 0;
    while (query[i] == ' ') i++;
    while (query[i] != '\0' && n < 10) {
        int j = 0;
        while (query[i] != ' ' && query[i] != '\0' && j < 63) {
            tokens[n][j++] = query[i++];
        }
        tokens[n][j] = '\0';
        n++;
        while (query[i] == ' ') i++;
    }
    if (n == 0) return;

    const char* cmd = tokens[0];

    if (strcmp(cmd, "PRINT") == 0 && n >= 2) {
        const char* name = tokens[1];
        ArrayEntry* a = s->arrays;
        while (a) { if (strcmp(a->name, name) == 0) { if (!quiet) arrayPrint(a->array); return; } a = a->next; }
        FListEntry* f = s->flists;
        while (f) { if (strcmp(f->name, name) == 0) { if (!quiet) flistPrint(f->list); return; } f = f->next; }
        ListEntry* l = s->lists;
        while (l) { if (strcmp(l->name, name) == 0) { if (!quiet) listPrint(l->list); return; } l = l->next; }
        StackEntry* st = s->stacks;
        while (st) { if (strcmp(st->name, name) == 0) { if (!quiet) stackPrint(st->stack); return; } st = st->next; }
        QueueEntry* q = s->queues;
        while (q) { if (strcmp(q->name, name) == 0) { if (!quiet) queuePrint(q->queue); return; } q = q->next; }
        TreeEntry* t = s->trees;
        while (t) { if (strcmp(t->name, name) == 0) { if (!quiet) avlPrint(t->tree); return; } t = t->next; }
        if (!quiet) cout << "Not found: " << name << endl;
        return;
    }

    if (n < 2) { if (!quiet) cout << "Bad command" << endl; return; }
    const char* name = tokens[1];

    if (strcmp(cmd, "SPUSH") == 0 && n >= 3) {
        Stack* st = storageGetStack(s, name);
        int v = atoi(tokens[2]);
        stackPush(st, v);
        if (!quiet) cout << v << endl;
    }
    else if (strcmp(cmd, "SPOP") == 0) {
        Stack* st = storageGetStack(s, name);
        int v = stackPop(st);
        if (v != -1 && !quiet) cout << v << endl;
    }
    else if (strcmp(cmd, "SGET") == 0) {
        Stack* st = storageGetStack(s, name);
        int v = stackGet(st);
        if (v != -1 && !quiet) cout << v << endl;
    }

    else if (strcmp(cmd, "QPUSH") == 0 && n >= 3) {
        Queue* q = storageGetQueue(s, name);
        int v = atoi(tokens[2]);
        queuePush(q, v);
        if (!quiet) cout << v << endl;
    }
    else if (strcmp(cmd, "QPOP") == 0) {
        Queue* q = storageGetQueue(s, name);
        int v = queuePop(q);
        if (v != -1 && !quiet) cout << v << endl;
    }
    else if (strcmp(cmd, "QGET") == 0) {
        Queue* q = storageGetQueue(s, name);
        int v = queueGet(q);
        if (v != -1 && !quiet) cout << v << endl;
    }

    else if (strcmp(cmd, "MPUSH") == 0 && n >= 3) {
        Array* a = storageGetArray(s, name);
        int v = atoi(tokens[2]);
        if (n >= 4) {
            int idx = atoi(tokens[3]);
            arrayPushAt(a, v, idx);
        } else {
            arrayPush(a, v);
        }
        if (!quiet) cout << v << endl;
    }
    else if (strcmp(cmd, "MDEL") == 0 && n >= 3) {
        Array* a = storageGetArray(s, name);
        int idx = atoi(tokens[2]);
        int v = arrayDel(a, idx);
        if (v != -1 && !quiet) cout << v << endl;
    }
    else if (strcmp(cmd, "MGET") == 0 && n >= 3) {
        Array* a = storageGetArray(s, name);
        int idx = atoi(tokens[2]);
        int v = arrayGet(a, idx);
        if (v != -1 && !quiet) cout << v << endl;
    }
    else if (strcmp(cmd, "MSET") == 0 && n >= 4) {
        Array* a = storageGetArray(s, name);
        int idx = atoi(tokens[2]);
        int v = atoi(tokens[3]);
        arraySet(a, idx, v);
        if (!quiet) cout << v << endl;
    }
    else if (strcmp(cmd, "MLEN") == 0) {
        Array* a = storageGetArray(s, name);
        if (!quiet) cout << arrayLen(a) << endl;
    }

    else if (strcmp(cmd, "TINSERT") == 0 && n >= 3) {
        AVLTree* t = storageGetTree(s, name);
        int v = atoi(tokens[2]);
        avlInsert(t, v);
        if (!quiet) cout << v << endl;
    }
    else if (strcmp(cmd, "TDEL") == 0 && n >= 3) {
        AVLTree* t = storageGetTree(s, name);
        int v = atoi(tokens[2]);
        bool ok = avlDel(t, v);
        if (!quiet) cout << (ok ? "TRUE" : "FALSE") << endl;
    }
    else if (strcmp(cmd, "TSEARCH") == 0 && n >= 3) {
        AVLTree* t = storageGetTree(s, name);
        int v = atoi(tokens[2]);
        bool ok = avlSearch(t, v);
        if (!quiet) cout << (ok ? "TRUE" : "FALSE") << endl;
    }
    else if (strcmp(cmd, "TGET") == 0) {
        AVLTree* t = storageGetTree(s, name);
        if (!quiet) avlPrint(t);
    }

    else if (strcmp(cmd, "FPUSH") == 0 && n >= 3) {
        ForwardList* fl = storageGetFList(s, name);
        int v = atoi(tokens[2]);
        if (n == 3) { flistPushTail(fl, v); }
        else if (strcmp(tokens[3], "head") == 0) { flistPushHead(fl, v); }
        else if (strcmp(tokens[3], "tail") == 0) { flistPushTail(fl, v); }
        else if (strcmp(tokens[3], "before") == 0 && n >= 5) { flistPushBefore(fl, atoi(tokens[4]), v); }
        else if (strcmp(tokens[3], "after") == 0 && n >= 5) { flistPushAfter(fl, atoi(tokens[4]), v); }
        if (!quiet) cout << v << endl;
    }

    else if (strcmp(cmd, "FGET") == 0 && n >= 3) {
        ForwardList* fl = storageGetFList(s, name);
        int result = -1;
        
        if (strcmp(tokens[2], "head") == 0) {
            result = flistGetHead(fl);
        }
        else if (strcmp(tokens[2], "tail") == 0) {
            result = flistGetTail(fl);
        }
        else {
            int idx = atoi(tokens[2]);
            result = flistGetAt(fl, idx);
        }
        
        if (result != -1 && !quiet) cout << result << endl;
    }

    else if (strcmp(cmd, "FDEL") == 0 && n >= 3) {
        ForwardList* fl = storageGetFList(s, name);

        if (strcmp(tokens[2], "head") == 0) {
            int v = flistDelHead(fl);
            if (v != -1 && !quiet) cout << v << endl;
        }
        else if (strcmp(tokens[2], "tail") == 0) {
            int v = flistDelTail(fl);
            if (v != -1 && !quiet) cout << v << endl;
        }
        else if (strcmp(tokens[2], "before") == 0 && n >= 4) {
            int v = flistDelBefore(fl, atoi(tokens[3]));
            if (v != -1 && !quiet) cout << v << endl;
        }
        else if (strcmp(tokens[2], "after") == 0 && n >= 4) {
            int v = flistDelAfter(fl, atoi(tokens[3]));
            if (v != -1 && !quiet) cout << v << endl;
        }
        else {
            flistDelValue(fl, atoi(tokens[2]));
        }
    }
    else if (strcmp(cmd, "FSEARCH") == 0 && n >= 3) {
        ForwardList* fl = storageGetFList(s, name);
        bool ok = flistSearch(fl, atoi(tokens[2]));
        if (!quiet) cout << (ok ? "TRUE" : "FALSE") << endl;
    }

    else if (strcmp(cmd, "LPUSH") == 0 && n >= 3) {
        List* l = storageGetList(s, name);
        int v = atoi(tokens[2]);
        if (n == 3) { listPushTail(l, v); }
        else if (strcmp(tokens[3], "head") == 0) { listPushHead(l, v); }
        else if (strcmp(tokens[3], "tail") == 0) { listPushTail(l, v); }
        else if (strcmp(tokens[3], "before") == 0 && n >= 5) { listPushBefore(l, atoi(tokens[4]), v); }
        else if (strcmp(tokens[3], "after") == 0 && n >= 5) { listPushAfter(l, atoi(tokens[4]), v); }
        if (!quiet) cout << v << endl;
    }
        else if (strcmp(cmd, "LGET") == 0 && n >= 3) {
        List* l = storageGetList(s, name);
        int result = -1;
        
        if (strcmp(tokens[2], "head") == 0) {
            result = listGetHead(l);
        }
        else if (strcmp(tokens[2], "tail") == 0) {
            result = listGetTail(l);
        }
        else {
            int idx = atoi(tokens[2]);
            result = listGetAt(l, idx);
        }
        
        if (result != -1 && !quiet) cout << result << endl;
    }

    else if (strcmp(cmd, "LDEL") == 0 && n >= 2) {
        List* l = storageGetList(s, name);
        if (strcmp(tokens[2], "head") == 0) {
            int v = listDelHead(l);
            if (v != -1 && !quiet) cout << v << endl;
        }
        else if (strcmp(tokens[2], "tail") == 0) {
            int v = listDelTail(l);
            if (v != -1 && !quiet) cout << v << endl;
        }
        else if (strcmp(tokens[2], "before") == 0 && n >= 4) {
            int v = listDelBefore(l, atoi(tokens[3]));
            if (v != -1 && !quiet) cout << v << endl;
        }
        else if (strcmp(tokens[2], "after") == 0 && n >= 4) {
            int v = listDelAfter(l, atoi(tokens[3]));
            if (v != -1 && !quiet) cout << v << endl;
        }
        else {
            listDelValue(l, atoi(tokens[2]));
        }
    }
    else if (strcmp(cmd, "LSEARCH") == 0 && n >= 3) {
        List* l = storageGetList(s, name);
        bool ok = listSearch(l, atoi(tokens[2]));
        if (!quiet) cout << (ok ? "TRUE" : "FALSE") << endl;
    }

    else {
        if (!quiet) cout << "Unknown command: " << cmd << endl;
    }
}

void storageLoad(Storage* s, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) return;
    char line[256];
    while (file.getline(line, 256)) {
        if (strlen(line) == 0) continue;
        storageExecute(s, line, true);
    }
    file.close();
}

void storageSave(Storage* s, const char* filename) {
    ofstream file(filename);
    if (!file.is_open()) return;

    StackEntry* st = s->stacks;
    while (st) {
        int buf[1000];
        int cnt = 0;
        SNode* cur = st->stack->head;
        while (cur) { buf[cnt++] = cur->data; cur = cur->next; }
        for (int i = cnt - 1; i >= 0; i--) {
            file << "SPUSH " << st->name << " " << buf[i] << "\n";
        }
        st = st->next;
    }

    QueueEntry* q = s->queues;
    while (q) {
        QNode* cur = q->queue->head;
        while (cur) {
            file << "QPUSH " << q->name << " " << cur->data << "\n";
            cur = cur->next;
        }
        q = q->next;
    }

    ArrayEntry* a = s->arrays;
    while (a) {
        for (int i = 0; i < a->array->size; i++) {
            file << "MPUSH " << a->name << " " << a->array->data[i] << "\n";
        }
        a = a->next;
    }

    FListEntry* f = s->flists;
    while (f) {
        FNode* cur = f->list->head;
        while (cur) {
            file << "FPUSH " << f->name << " " << cur->data << "\n";
            cur = cur->next;
        }
        f = f->next;
    }

    ListEntry* l = s->lists;
    while (l) {
        LNode* cur = l->list->head;
        while (cur) {
            file << "LPUSH " << l->name << " " << cur->data << "\n";
            cur = cur->next;
        }
        l = l->next;
    }

    TreeEntry* t = s->trees;
    while (t) {
        int buf[1000];
        int cnt = avlToArray(t->tree, buf);
        for (int i = 0; i < cnt; i++) {
            file << "TINSERT " << t->name << " " << buf[i] << "\n";
        }
        t = t->next;
    }

    file.close();
}