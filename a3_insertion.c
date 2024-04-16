#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int rank; // -> dist to the nearest null child
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->rank = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *merge(Node *h1, Node *h2) {
    if (h1 == NULL) return h2;
    if (h2 == NULL) return h1;

    // -> h1 always points to smaller value
    if (h1->data > h2->data) { 
        Node *temp = h1;
        h1 = h2;
        h2 = temp;
    }

    h1->right = merge(h1->right, h2);
    if (h1->left == NULL || h1->right->rank > h1->left->rank) { // Swap left and right if needed
        Node *temp = h1->left;
        h1->left = h1->right;
        h1->right = temp;
    }
    if (h1->right == NULL) h1->rank = 0; 
    else h1->rank = h1->right->rank + 1;
    return h1;
}

Node *insert(Node *root, int data) {
    Node *node = newNode(data);
    return merge(root, node);
}

// -> preorder traversal
void preorder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main() {
    Node *root = NULL;
    int nums[] = {77, 22, 9, 68, 16, 34, 13, 8, 55};
    int n = sizeof(nums) / sizeof(nums[0]);

    printf("Inserting elems into leftist heap:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", nums[i]);
        root = insert(root, nums[i]);
    }

    printf("\nPreorder traversal after insertion:\n");
    preorder(root);
    printf("\n");

    return 0;
}
