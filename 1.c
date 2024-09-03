#include <stdio.h>

#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {

int data;

Color color;

struct Node *left, *right, *parent;

} Node;

Node* createNode(int data) {

Node *node = (Node*)malloc(sizeof(Node));

node->data = data;

node->color = RED;

node->left = node->right = node->parent = NULL;

return node;

}

Node* rotateLeft(Node *root, Node *x) {

Node *y = x->right;

x->right = y->left;

if (y->left != NULL)

y->left->parent = x;

y->parent = x->parent;

if (x->parent == NULL)

root = y;

else if (x == x->parent->left)

x->parent->left = y;

else

x->parent->right = y;

y->left = x;

x->parent = y;

return root;

}

Node* rotateRight(Node *root, Node *y) {

Node *x = y->left;
y->left = x->right;

if (x->right != NULL)

x->right->parent = y;

x->parent = y->parent;

if (y->parent == NULL)

root = x;

else if (y == y->parent->left)

y->parent->left = x;

else

y->parent->right = x;

x->right = y;

y->parent = x;

return root;

}

Node* insertFixup(Node *root, Node *z) {

while (z->parent && z->parent->color == RED) {

if (z->parent == z->parent->parent->left) {

Node *y = z->parent->parent->right;

if (y && y->color == RED) {

z->parent->color = BLACK;

y->color = BLACK;

z->parent->parent->color = RED;

z = z->parent->parent;

} else {

if (z == z->parent->right) {

z = z->parent;

root = rotateLeft(root, z);

}

z->parent->color = BLACK;

z->parent->parent->color = RED;

root = rotateRight(root, z->parent->parent);

}

} else {

Node *y = z->parent->parent->left;

if (y && y->color == RED) {

z->parent->color = BLACK;

y->color = BLACK;

z->parent->parent->color = RED;

z = z->parent->parent;

} else {

if (z == z->parent->left) {

z = z->parent;

root = rotateRight(root, z);
}

z->parent->color = BLACK;

z->parent->parent->color = RED;

root = rotateLeft(root, z->parent->parent);

}

}

}

root->color = BLACK;

return root;

}

Node* insert(Node *root, int data) {

Node *z = createNode(data);

Node *y = NULL;

Node *x = root;

while (x != NULL) {

y = x;

if (z->data < x->data)

x = x->left;

else

x = x->right;

}

z->parent = y;

if (y == NULL)

root = z;

else if (z->data < y->data)

y->left = z;

else

y->right = z;

return insertFixup(root, z);

}

Node* minimum(Node *x) {

while (x->left != NULL)

x = x->left;

return x;

}

Node* deleteFixup(Node *root, Node *x) {

while (x != root && (!x || x->color == BLACK)) {

if (x == x->parent->left) {
Node *w = x->parent->right;

if (w->color == RED) {

w->color = BLACK;

x->parent->color = RED;

root = rotateLeft(root, x->parent);

w = x->parent->right;

}

if ((!w->left || w->left->color == BLACK) &&

(!w->right || w->right->color == BLACK)) {

w->color = RED;

x = x->parent;

} else {

if (!w->right || w->right->color == BLACK) {

if (w->left) w->left->color = BLACK;

w->color = RED;

root = rotateRight(root, w);

w = x->parent->right;

}

w->color = x->parent->color;

x->parent->color = BLACK;

if (w->right) w->right->color = BLACK;

root = rotateLeft(root, x->parent);

x = root;

}

} else {

Node *w = x->parent->left;

if (w->color == RED) {

w->color = BLACK;

x->parent->color = RED;

root = rotateRight(root, x->parent);

w = x->parent->left;

}

if ((!w->right || w->right->color == BLACK) &&

(!w->left || w->left->color == BLACK)) {

w->color = RED;

x = x->parent;

} else {

if (!w->left || w->left->color == BLACK) {

if (w->right) w->right->color = BLACK;

w->color = RED;

root = rotateLeft(root, w);

w = x->parent->left;

}

w->color = x->parent->color;
x->parent->color = BLACK;

if (w->left) w->left->color = BLACK;

root = rotateRight(root, x->parent);

x = root;

}

}

}

if (x) x->color = BLACK;

return root;

}

Node* deleteNode(Node *root, Node *z) {

Node *y = z;

Node *x;

Color originalColor = y->color;

if (z->left == NULL) {

x = z->right;

if (z->parent == NULL)

root = x;

else if (z == z->parent->left)

z->parent->left = x;

else

z->parent->right = x;

if (x) x->parent = z->parent;

} else if (z->right == NULL) {

x = z->left;

if (z->parent == NULL)

root = x;

else if (z == z->parent->left)

z->parent->left = x;

else

z->parent->right = x;

if (x) x->parent = z->parent;

} else {

y = minimum(z->right);

originalColor = y->color;

x = y->right;

if (y->parent == z) {

if (x) x->parent = y;

} else {

if (y->parent) {

if (y == y->parent->left)

y->parent->left = x;
else

y->parent->right = x;

}

y->right = z->right;

if (y->right) y->right->parent = y;

}

if (z->parent == NULL)

root = y;

else if (z == z->parent->left)

z->parent->left = y;

else

z->parent->right = y;

y->parent = z->parent;

y->color = z->color;

y->left = z->left;

if (y->left) y->left->parent = y;

}

if (originalColor == BLACK)

root = deleteFixup(root, x);

free(z);

return root;

}

Node* search(Node *root, int data) {

while (root != NULL && data != root->data) {

if (data < root->data)

root = root->left;

else

root = root->right;

}

return root;

}

void inorderTraversal(Node *root) {

if (root != NULL) {

inorderTraversal(root->left);

printf("%d ", root->data);

inorderTraversal(root->right);

}

}

void preorderTraversal(Node *root) {
  if (root != NULL) {

printf("%d ", root->data);

preorderTraversal(root->left);

preorderTraversal(root->right);

}

}

void postorderTraversal(Node *root) {

if (root != NULL) {

postorderTraversal(root->left);

postorderTraversal(root->right);

printf("%d ", root->data);

}

}

int main() {

Node *root = NULL;

root = insert(root, 10);

root = insert(root, 20);

root = insert(root, 30);

root = insert(root, 15);

root = insert(root, 25);

root = insert(root, 5);

root = insert(root, 1);

printf("Inorder Traversal: ");

inorderTraversal(root);

printf("\n");

printf("Preorder Traversal: ");

preorderTraversal(root);

printf("\n");

printf("Postorder Traversal: ");

postorderTraversal(root);

printf("\n");

Node *searchedNode = search(root, 15);

if (searchedNode != NULL)

printf("Node 15 found in the tree.\n");

else

printf("Node 15 not found in the tree.\n");
root = deleteNode(root, search(root, 20));

printf("After deleting 20, Inorder Traversal: ");

inorderTraversal(root);

printf("\n");

root = deleteNode(root, search(root, 5));

printf("After deleting 5, Inorder Traversal: ");

inorderTraversal(root);

printf("\n");

root = deleteNode(root, search(root, 15));

printf("After deleting 15, Inorder Traversal: ");

inorderTraversal(root);

printf("\n");

return 0;
}
