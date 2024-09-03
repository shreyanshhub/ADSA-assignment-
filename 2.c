#include <stdio.h>

#include <stdlib.h>

#define RED 0

#define BLACK 1

typedef struct Node {

int data;

int color;

struct Node* left;

struct Node* right;

struct Node* parent;

} Node;

Node* createNode(int data, int color) {

Node* node = (Node*)malloc(sizeof(Node));

node->data = data;

node->color = color;

node->left = node->right = node->parent = NULL;

return node;

}
int isRedBlackTree(Node* root) {

if (root == NULL) return 1;

if (root->color != BLACK) return 0;

int leftBlackHeight = 0, rightBlackHeight = 0;

if (!validateProperties(root, &leftBlackHeight, &rightBlackHeight))

return 0;

return leftBlackHeight == rightBlackHeight;

}

int validateProperties(Node* node, int* leftBlackHeight, int* rightBlackHeight) {

if (node == NULL) {

*leftBlackHeight = *rightBlackHeight = 1;

return 1;

}

int leftChildHeight = 0, rightChildHeight = 0;

if (node->color == RED) {

if ((node->left && node->left->color != BLACK) ||

(node->right && node->right->color != BLACK))

return 0;

}

if (!validateProperties(node->left, &leftChildHeight, &rightChildHeight))

return 0;

*leftBlackHeight = leftChildHeight + (node->color == BLACK ? 1 : 0);

*rightBlackHeight = rightChildHeight + (node->color == BLACK ? 1 : 0);

if (*leftBlackHeight != *rightBlackHeight)

return 0;

return validateProperties(node->right, leftBlackHeight, rightBlackHeight);

}
