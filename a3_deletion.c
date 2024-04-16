#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int rank; 
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->rank = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
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
    Node *new_node = newNode(data);
    return merge(root, new_node);
}

Node *deleteMin(Node *root) {
    if (!root) return NULL;
    Node *left_child = root->left;
    Node *right_child = root->right;
    free(root);
    return merge(left_child, right_child);
}

void inorderTraversal(Node *root) {
    if (root) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void preorder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main() {
    Node *root = NULL;

    // Inserting elements: 77, 22, 9, 68, 16, 34, 13, 8
    root = insert(root, 77);
    root = insert(root, 22);
    root = insert(root, 9);
    root = insert(root, 68);
    root = insert(root, 16);
    root = insert(root, 34);
    root = insert(root, 13);
    root = insert(root, 8);
    printf("Preorder traversal after insertion: ");
    preorder(root);
    printf("\n\n");

    printf("Deleting min elems one by one:\n");
    while (root) {
        printf("Min elem: %d\n", root->data);
        root = deleteMin(root);
        printf("Inorder traversal after deletion: ");
        inorderTraversal(root);
        printf("\n\n");
    }

    return 0;
}
