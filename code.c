#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDREN 100

typedef struct BTreeNode {
    int *keys;
    int t;
    int n;
    struct BTreeNode **C;
} BTreeNode;

BTreeNode *newBTreeNode(int _t) {
    BTreeNode *newNode = (BTreeNode *) malloc(sizeof(BTreeNode));
    newNode->keys = (int *) malloc((2 * _t - 1) * sizeof(int));
    newNode->C = (BTreeNode **) malloc((2 * _t) * sizeof(BTreeNode *));
    newNode->t = _t;
    newNode->n = 0;
    return newNode; // Don't forget to return the newly allocated node
}

void traverse(BTreeNode *root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (root->C[i] != NULL)
            traverse(root->C[i]);
        printf("%d ", root->keys[i]);
    }
    if (root->C[i] != NULL)
        traverse(root->C[i]);
}

void insertNonFull(BTreeNode *root, int k) {
    int i = root->n - 1;
    if (root->n == 2 * root->t - 1) {
        BTreeNode *newRoot = newBTreeNode(root->t);
        newRoot->C[0] = root;
        splitChild(newRoot, 0, root);
        i = 0;
        if (k > newRoot->keys[0])
            i++;
        insertNonFull(newRoot->C[i], k);
        return;
    }
    while (i >= 0 && root->keys[i] > k) {
        root->keys[i + 1] = root->keys[i];
        i--;
    }
    root->keys[i + 1] = k;
    root->n++;
}

void splitChild(BTreeNode *parent, int i, BTreeNode *child) {
    BTreeNode *newNode = newBTreeNode(child->t);
    newNode->n = child->t - 1;
    for (int j = 0; j < child->t - 1; j++)
        newNode->keys[j] = child->keys[j + child->t];
    if (child->C != NULL) {
        for (int j = 0; j < child->t + 1; j++) // Fixed array index out of bounds
            newNode->C[j] = child->C[j + child->t];
    }
    child->n = child->t - 1;
    for (int j = parent->n; j >= i + 1; j--)
        parent->C[j + 1] = parent->C[j];
    parent->C[i + 1] = newNode;
    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = child->keys[child->t - 1];
    parent->n++;
}

void insert(BTreeNode *root, int k) {
    if (root->n == 0) {
        root->keys[0] = k;
        root->n++;
    } else {
        insertNonFull(root, k);
    }
}

int main() {
    BTreeNode *root = newBTreeNode(3);
    insert(root, 10);
    insert(root, 20);
    insert(root, 30);
    insert(root, 40);
    insert(root, 50);
    traverse(root);
    return 0;
}
