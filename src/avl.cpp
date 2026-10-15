#include <iostream>
#include <queue>
#include "avl.h"

using namespace std;

static int height(TNode* node){
    if (node == nullptr){return 0;}
    return node->height;
}

static void updateHeight(TNode* node){
    int hl = height(node->left);
    int hr = height(node->right);
    node->height = (hl > hr ? hl : hr) + 1;
}

static int balanceFactor(TNode* node){
    if (node == nullptr){return 0;}
    return height(node->left) - height(node->right);
}

static TNode* createNode(int value){
    TNode* node = new TNode;
    node->data = value;
    node->height = 1;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

static TNode* rotateRight(TNode* y){
    TNode* x = y->left;
    TNode* B = x->right;
    x->right = y;
    y->left = B;
    updateHeight(y);
    updateHeight(x);
    return x;
}

static TNode* rotateLeft(TNode* x){
    TNode* y = x->right;
    TNode* B = y->left;
    y->left = x;
    x->right = B;
    updateHeight(x);
    updateHeight(y);
    return y;
}

static TNode* balance(TNode* node){
    updateHeight(node);
    int bf = balanceFactor(node);

    if (bf > 1 && balanceFactor(node->left) >= 0){
        return rotateRight(node);
    }
    if (bf > 1 && balanceFactor(node->left) < 0){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (bf < -1 && balanceFactor(node->right) <= 0){
        return rotateLeft(node);
    }
    if (bf < -1 && balanceFactor(node->right) > 0){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

static TNode* insertNode(TNode* node, int value){
    if (node == nullptr){
        return createNode(value);
    }
    if (value < node->data){
        node->left = insertNode(node->left, value);
    }else if(value > node->data){
        node->right = insertNode(node->right, value);
    }else{
        return node;
    }
    return balance(node);
}

void avlInsert(AVLTree* tree, int value){
    tree->root = insertNode(tree->root, value);
    tree->size++;
}

static TNode* searchNode(TNode* node, int value){
    if (node == nullptr){return nullptr;}
    if (value == node->data){return node;}
    if (value < node->data){return searchNode(node->left, value);}
    return searchNode(node->right, value);
}

bool avlSearch(AVLTree* tree, int value){
    return searchNode(tree->root, value) != nullptr;
}

static TNode* findMin(TNode* node){
    while (node->left != nullptr){
        node = node->left;
    }
    return node;
}

static TNode* deleteNode(TNode* node, int value, int& out, bool& deleted){
    if (node == nullptr){return nullptr;}
    if (value < node->data){
        node->left = deleteNode(node->left, value, out, deleted);
    }else if (value > node->data){
        node->right = deleteNode(node->right, value, out, deleted);
    }else{
        if (!deleted) {
            out = node->data;
            deleted = true;
        }
        if (node->left == nullptr || node->right == nullptr){
            TNode* child = (node->left != nullptr) ? node->left : node->right;
            if (child == nullptr){
                delete node;
                return nullptr;
            }else{
                delete node;
                return child;
            }
        }else{
            TNode* successor = findMin(node->right);
            node->data = successor->data;
            node->right = deleteNode(node->right, successor->data, out, deleted);
        }
    }
    return balance(node);
}

bool avlDel(AVLTree* tree, int value, int& out){
    bool deleted = false;
    tree->root = deleteNode(tree->root, value, out, deleted);
    if (deleted) tree->size--;
    return deleted;
}

static void inorder(TNode* node){
    if (node == nullptr){return; }
    inorder(node->left);
    cout << node->data << endl;
    inorder(node->right);
}

static void preorder(TNode* node){
    if (node == nullptr){return; }
    cout << node->data << endl;
    preorder(node->left);
    preorder(node->right);
}

static void postorder(TNode* node){
    if (node == nullptr){return; }
    postorder(node->left);
    postorder(node->right);
    cout << node->data << endl;
}

static void printBFS(TNode* root) {
    if (!root) return;

    queue<TNode*> q;
    q.push(root);

    while (!q.empty()) {
        TNode* cur = q.front();
        q.pop();
        cout << "  " << cur->data << endl;

        if (cur->left)  q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

void avlPrintBFS(AVLTree* t) {
    if (!t->root) {
        cout << "TREE: empty" << endl;
        return;
    }
    cout << "TREE (bfs):" << endl;
    printBFS(t->root);
}

void avlPrintInorder(AVLTree* tree) {
    if (tree->root == nullptr) {
        cout << "TREE: empty" << endl;
        return;
    }
    cout << "TREE (inorder):" << endl;
    inorder(tree->root);
}

void avlPrintPreorder(AVLTree* tree) {
    if (tree->root == nullptr) {
        cout << "TREE: empty" << endl;
        return;
    }
    cout << "TREE (preorder):" << endl;
    preorder(tree->root);
}

void avlPrintPostorder(AVLTree* tree) {
    if (tree->root == nullptr) {
        cout << "TREE: empty" << endl;
        return;
    }
    cout << "TREE (postorder):" << endl;
    postorder(tree->root);
}

void avlPrint(AVLTree* tree) {
    avlPrintInorder(tree);
}

void avlInit(AVLTree* tree){
    tree->root = nullptr;
    tree->size = 0;
}

static void freeNode(TNode* node){
    if (node == nullptr){return;}
    freeNode(node->left);
    freeNode(node->right);
    delete node;
}

void avlFree(AVLTree* tree) {
    freeNode(tree->root);
    tree->root = nullptr;
    tree->size = 0;
}

bool avlIsEmpty(AVLTree* tree) {
    return tree->root == nullptr;
}

int avlLen(AVLTree* tree) {
    return tree->size;
}

static void fillArray(TNode* node, int* buf, int* idx) {
    if (node == nullptr) return;
    fillArray(node->left, buf, idx);
    buf[(*idx)++] = node->data;
    fillArray(node->right, buf, idx);
}

int avlToArray(AVLTree* tree, int* buf) {
    int idx = 0;
    fillArray(tree->root, buf, &idx);
    return idx;
}