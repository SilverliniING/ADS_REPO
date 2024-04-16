#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// -> rotate right at the given node (Zig operation)
struct Node* rotateRight(struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// -> rotate left at the given node (Zag operation)
struct Node* rotateLeft(struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    // -> BST insertion
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        return root; 
    }

    if (root->left && root->left->key == key) {
        return rotateRight(root);
    }
    if (root->right && root->right->key == key) {
        return rotateLeft(root);
    }

    return root;
}

// -> bottom-up insertion in a Splay Tree
struct Node* splayInsert(struct Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    root = insert(root, key);

    if (root->key == key)
        return root;

    if (key < root->key) {
        root->left = splayInsert(root->left, key);
        return rotateRight(root);
    }

    if (key > root->key) {
        root->right = splayInsert(root->right, key);
        return rotateLeft(root);
    }

    return root;
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    // 20, 10, 30, 40, 45, 56, 70
    root = splayInsert(root, 20);
    root = splayInsert(root, 10);
    root = splayInsert(root, 30);
    root = splayInsert(root, 40);
    root = splayInsert(root, 45);
    root = splayInsert(root, 56);
    root = splayInsert(root, 70);

    printf("Inorder traversal of the Splay Tree after insertion: ");
    inorder(root);
    printf("\n");

    return 0;
}
