#include <stdio.h>
#include <stdlib.h>

// Structure of a Splay Tree Node
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Function to create a new Splay Tree Node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Function to rotate right at the given node (Zig operation)
struct Node* rotateRight(struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Function to rotate left at the given node (Zag operation)
struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Function to perform top-down deletion in a Splay Tree
struct Node* splayDelete(struct Node* root, int key) {
    if (root == NULL)
        return NULL;

    if (key < root->key) {
        root->left = splayDelete(root->left, key);
        return root;
    }
    if (key > root->key) {
        root->right = splayDelete(root->right, key);
        return root;
    }

    if (root->left == NULL) {
        struct Node* temp = root->right;
        free(root);
        return temp;
    } else if (root->right == NULL) {
        struct Node* temp = root->left;
        free(root);
        return temp;
    }

    // Node to be deleted has both children
    struct Node* temp = root->right;
    while (temp->left != NULL)
        temp = temp->left;

    root->key = temp->key;
    root->right = splayDelete(root->right, temp->key);
    return root;
}

// Function to perform inorder traversal of a Splay Tree
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Driver program
int main() {
    // Creating the initial Splay Tree: 20, 10, 30, 40, 45, 56, 70
    struct Node* root = newNode(20);
    root->left = newNode(10);
    root->right = newNode(30);
    root->right->right = newNode(40);
    root->right->right->right = newNode(45);
    root->right->right->right->right = newNode(56);
    root->right->right->right->right->right = newNode(70);

    // Print the inorder traversal of the initial Splay Tree
    printf("Inorder traversal of the initial Splay Tree: ");
    inorder(root);
    printf("\n");

    // Deleting element 45 from the Splay Tree
    root = splayDelete(root, 45);

    // Print the inorder traversal of the Splay Tree after deletion
    printf("Inorder traversal of the Splay Tree after deletion: ");
    inorder(root);
    printf("\n");

    return 0;
}
