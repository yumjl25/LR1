#ifndef ARRAY_H
#define ARRAY_H

struct Array {
    int* data;
    int size;
    int capacity;
};

void arrayInit(Array* a);
void arrayFree(Array* a);

bool arrayIsEmpty(Array* a);
int  arrayLen(Array* a);

void arrayPush(Array* a, int value);
void arrayPushAt(Array* a, int value, int index);
int  arrayGet(Array* a, int index);
void arraySet(Array* a, int index, int value);
int  arrayDel(Array* a, int index);               

void arrayPrint(Array* a);

#endif