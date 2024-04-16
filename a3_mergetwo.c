#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node *merge(Node *h1, Node *h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    if (h1->data > h2->data) {
        Node *temp = h1;
        h1 = h2;
        h2 = temp;
    }

    // -> recursively merge h1's right subtree with h2
    Node *temp = h1->right;
    h1->right = h1->left;
    h1->left = merge(h2, temp);

    return h1;
}

void preorderTraversal(Node *root) {
    if (root) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

int main() {
    // -> heap 1: 2 -> 4 -> 22
    Node *heap1 = newNode(2);
    heap1->left = newNode(4);
    heap1->right = newNode(22);

    // -> heap 2: 12 -> 18 -> 90
    Node *heap2 = newNode(12);
    heap2->left = newNode(18);
    heap2->right = newNode(90);

    printf("Heap 1 preorder traversal: ");
    preorderTraversal(heap1);
    printf("\n");

    printf("Heap 2 preorder traversal: ");
    preorderTraversal(heap2);
    printf("\n");

    Node *mergedHeap = merge(heap1, heap2);

    printf("Merged heap preorder traversal: ");
    preorderTraversal(mergedHeap);
    printf("\n");

    return 0;
}