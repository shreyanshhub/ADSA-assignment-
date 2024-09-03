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

typedef struct QueueNode {

Node* treeNode;

int level;

struct QueueNode* next;

} QueueNode;

typedef struct Queue {

QueueNode* front;

QueueNode* rear;

} Queue;

Queue* createQueue() {

Queue* queue = (Queue*)malloc(sizeof(Queue));

queue->front = queue->rear = NULL;

return queue;

}

void enqueue(Queue* queue, Node* node, int level) {

QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));

newQueueNode->treeNode = node;

newQueueNode->level = level;

newQueueNode->next = NULL;

if (queue->rear) {

queue->rear->next = newQueueNode;

} else {

queue->front = newQueueNode;

}

queue->rear = newQueueNode;

}

QueueNode* dequeue(Queue* queue) {

if (!queue->front) return NULL;

QueueNode* temp = queue->front;
queue->front = queue->front->next;

if (!queue->front) queue->rear = NULL;

return temp;

}

int isEmpty(Queue* queue) {

return queue->front == NULL;

}

int calculateBlackHeight(Node* node) {

if (!node) return 0;

int leftHeight = calculateBlackHeight(node->left);

int rightHeight = calculateBlackHeight(node->right);

int addBlack = (node->color == BLACK) ? 1 : 0;

return (leftHeight > rightHeight ? leftHeight : rightHeight) + addBlack;

}

void printLevelOrder(Node* root) {

if (!root) return;

Queue* queue = createQueue();

enqueue(queue, root, 0);

int currentLevel = 0;

int currentBlackHeight = calculateBlackHeight(root);

printf("Level %d: Black-Height = %d\n", currentLevel, currentBlackHeight);

while (!isEmpty(queue)) {

QueueNode* temp = dequeue(queue);

Node* currentNode = temp->treeNode;

int level = temp->level;

free(temp);

if (level > currentLevel) {

currentLevel = level;

currentBlackHeight = calculateBlackHeight(currentNode);

printf("\nLevel %d: Black-Height = %d\n", currentLevel, currentBlackHeight);

}

printf("%d(%s) ", currentNode->data, currentNode->color == RED ? "R" : "B");

if (currentNode->left) enqueue(queue, currentNode->left, level + 1);

if (currentNode->right) enqueue(queue, currentNode->right, level + 1);

}

printf("\n");

}
Node* createNode(int data, int color) {

Node* node = (Node*)malloc(sizeof(Node));

node->data = data;

node->color = color;

node->left = node->right = node->parent = NULL;

return node;

}

int main() {

Node* root = createNode(10, BLACK);

root->left = createNode(5, RED);

root->right = createNode(15, RED);

root->left->left = createNode(3, BLACK);

root->left->right = createNode(7, BLACK);

root->right->right = createNode(18, BLACK);

printLevelOrder(root);

return 0;

}
