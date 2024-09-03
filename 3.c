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

typedef struct {

Node* root;

int leftRotations;

int rightRotations;

int colorChanges;

} RBTree;

Node* createNode(int data) {

Node* node = (Node*)malloc(sizeof(Node));

node->data = data;

node->color = RED;

node->left = node->right = node->parent = NULL;

return node;

}

void rotateLeft(RBTree* tree, Node* x) {

Node* y = x->right;

x->right = y->left;

if (y->left) y->left->parent = x;

y->parent = x->parent;

if (!x->parent) tree->root = y;

else if (x == x->parent->left) x->parent->left = y;

else x->parent->right = y;

y->left = x;

x->parent = y;

tree->leftRotations++;

}

void rotateRight(RBTree* tree, Node* x) {

Node* y = x->left;

x->left = y->right;

if (y->right) y->right->parent = x;

y->parent = x->parent;

if (!x->parent) tree->root = y;
else if (x == x->parent->right) x->parent->right = y;

else x->parent->left = y;

y->right = x;

x->parent = y;

tree->rightRotations++;

}

void fixInsertion(RBTree* tree, Node* node) {

Node* parent = NULL;

Node* grandparent = NULL;

while ((node != tree->root) && (node->color != BLACK) && (node->parent->color == RED)) {

parent = node->parent;

grandparent = parent->parent;

if (parent == grandparent->left) {

Node* uncle = grandparent->right;

if (uncle && uncle->color == RED) {

grandparent->color = RED;

parent->color = BLACK;

uncle->color = BLACK;

node = grandparent;

tree->colorChanges += 3;

} else {

if (node == parent->right) {

rotateLeft(tree, parent);

node = parent;

parent = node->parent;

}

rotateRight(tree, grandparent);

int temp = parent->color;

parent->color = grandparent->color;

grandparent->color = temp;

tree->colorChanges += 2;

node = parent;

}

} else {

Node* uncle = grandparent->left;

if (uncle && uncle->color == RED) {

grandparent->color = RED;

parent->color = BLACK;

uncle->color = BLACK;

node = grandparent;

tree->colorChanges += 3;
} else {

if (node == parent->left) {

rotateRight(tree, parent);

node = parent;

parent = node->parent;

}

rotateLeft(tree, grandparent);

int temp = parent->color;

parent->color = grandparent->color;

grandparent->color = temp;

tree->colorChanges += 2;

node = parent;

}

}

}

tree->root->color = BLACK;

}

void insertNode(RBTree* tree, int data) {

Node* newNode = createNode(data);

Node* y = NULL;

Node* x = tree->root;

while (x) {

y = x;

if (newNode->data < x->data) x = x->left;

else x = x->right;

}

newNode->parent = y;

if (!y) tree->root = newNode;

else if (newNode->data < y->data) y->left = newNode;

else y->right = newNode;

fixInsertion(tree, newNode);

}

int main() {

RBTree tree = {NULL, 0, 0, 0};

insertNode(&tree, 10);

insertNode(&tree, 20);

insertNode(&tree, 30);

printf("Left Rotations: %d\n", tree.leftRotations);
printf("Right Rotations: %d\n", tree.rightRotations);

printf("Color Changes: %d\n", tree.colorChanges);

return 0;

}
