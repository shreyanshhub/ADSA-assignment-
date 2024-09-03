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

} RBTree;

Node* createNode(int data) {

Node* node = (Node*)malloc(sizeof(Node));

node->data = data;

node->color = RED;

node->left = node->right = node->parent = NULL;

return node;

}

Node* findMin(Node* node) {

while (node->left) node = node->left;

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

}

void fixDeletion(RBTree* tree, Node* x) {

while (x != tree->root && x->color == BLACK) {

if (x == x->parent->left) {

Node* sibling = x->parent->right;

if (sibling->color == RED) {

sibling->color = BLACK;

x->parent->color = RED;

rotateLeft(tree, x->parent);

sibling = x->parent->right;

}

if ((!sibling->left || sibling->left->color == BLACK) &&

(!sibling->right || sibling->right->color == BLACK)) {

sibling->color = RED;

x = x->parent;

} else {

if (!sibling->right || sibling->right->color == BLACK) {

sibling->left->color = BLACK;

sibling->color = RED;

rotateRight(tree, sibling);

sibling = x->parent->right;

}

sibling->color = x->parent->color;

x->parent->color = BLACK;

sibling->right->color = BLACK;

rotateLeft(tree, x->parent);

x = tree->root;
}

} else {

Node* sibling = x->parent->left;

if (sibling->color == RED) {

sibling->color = BLACK;

x->parent->color = RED;

rotateRight(tree, x->parent);

sibling = x->parent->left;

}

if ((!sibling->left || sibling->left->color == BLACK) &&

(!sibling->right || sibling->right->color == BLACK)) {

sibling->color = RED;

x = x->parent;

} else {

if (!sibling->left || sibling->left->color == BLACK) {

sibling->right->color = BLACK;

sibling->color = RED;

rotateLeft(tree, sibling);

sibling = x->parent->left;

}

sibling->color = x->parent->color;

x->parent->color = BLACK;

sibling->left->color = BLACK;

rotateRight(tree, x->parent);

x = tree->root;

}

}

}

x->color = BLACK;

}

void transplant(RBTree* tree, Node* u, Node* v) {

if (!u->parent) tree->root = v;

else if (u == u->parent->left) u->parent->left = v;

else u->parent->right = v;

if (v) v->parent = u->parent;

}

void deleteNode(RBTree* tree, Node* z) {

Node* y = z;

int yOriginalColor = y->color;

Node* x;

if (!z->left) {
x = z->right;

transplant(tree, z, z->right);

} else if (!z->right) {

x = z->left;

transplant(tree, z, z->left);

} else {

y = findMin(z->right);

yOriginalColor = y->color;

x = y->right;

if (y->parent == z) {

if (x) x->parent = y;

} else {

transplant(tree, y, y->right);

y->right = z->right;

y->right->parent = y;

}

transplant(tree, z, y);

y->left = z->left;

y->left->parent = y;

y->color = z->color;

}

if (yOriginalColor == BLACK && x) {

fixDeletion(tree, x);

}

free(z);

}

int main() {

RBTree tree = {NULL};

Node* node = createNode(10);

tree.root = node;

node->color = BLACK;

deleteNode(&tree, node);

return 0;

}
