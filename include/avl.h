#ifndef AVL_H
#define AVL_H

struct TNode{
    int data;
    int height;
    TNode* left;
    TNode* right;
};

struct AVLTree{
    TNode* root;
    int size;
};

void avlInit(AVLTree* tree);
void avlFree(AVLTree* tree);

bool avlIsEmpty(AVLTree* tree);
int avlLen(AVLTree* tree);

void avlInsert(AVLTree* tree, int value);
bool avlSearch(AVLTree* tree, int value);
bool avlDel(AVLTree* tree, int value, int& out);

void avlPrintInorder(AVLTree* tree);
void avlPrintPreorder(AVLTree* tree);
void avlPrintPostorder(AVLTree* tree);
void avlPrintBFS(AVLTree* tree);
void avlPrint(AVLTree* tree);
int avlToArray(AVLTree* tree, int* buf);

#endif