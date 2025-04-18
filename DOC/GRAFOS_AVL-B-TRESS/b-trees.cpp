// B-TREES  EJEMPLO EN C.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_KEYS 3  // Maximum keys per node (order-1)

// B+ Tree Node Structure
typedef struct BPlusNode {
    bool is_leaf;
    int num_keys;
    int keys[MAX_KEYS];
    struct BPlusNode* children[MAX_KEYS + 1];  // For non-leaf nodes
    struct BPlusNode* next;                    // For leaf nodes (linked list)
} BPlusNode;

// Create a new B+ Tree node
BPlusNode* create_node(bool is_leaf) {
    BPlusNode* node = (BPlusNode*)malloc(sizeof(BPlusNode));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->next = NULL;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Insert a key into the B+ Tree (simplified)
void insert(BPlusNode** root, int key) {
    if (*root == NULL) {
        *root = create_node(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
        return;
    }

    // For simplicity, this is a placeholder. Actual B+ insertion requires:
    // 1. Splitting nodes when they exceed MAX_KEYS.
    // 2. Propagating median keys to parent nodes.
    // 3. Maintaining linked leaves.
    printf("[Simplified] Key %d inserted (full B+ insertion logic not shown).\n", key);
}

// Search for a key in the B+ Tree
bool search(BPlusNode* root, int key) {
    if (root == NULL) return false;

    BPlusNode* cursor = root;
    while (!cursor->is_leaf) {
        for (int i = 0; i < cursor->num_keys; i++) {
            if (key < cursor->keys[i]) {
                cursor = cursor->children[i];
                break;
            }
            if (i == cursor->num_keys - 1) {
                cursor = cursor->children[i + 1];
                break;
            }
        }
    }

    for (int i = 0; i < cursor->num_keys; i++) {
        if (cursor->keys[i] == key) {
            return true;
        }
    }
    return false;
}

// Print the B+ Tree (in-order, leaves only)
void print_leaves(BPlusNode* root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    BPlusNode* cursor = root;
    while (!cursor->is_leaf) {
        cursor = cursor->children[0];
    }

    printf("Leaf nodes (linked list): ");
    while (cursor != NULL) {
        for (int i = 0; i < cursor->num_keys; i++) {
            printf("%d ", cursor->keys[i]);
        }
        cursor = cursor->next;
    }
    printf("\n");
}

int main() {
    BPlusNode* root = NULL;

    // Insert keys
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);
    insert(&root, 15);

    // Search keys
    printf("Search 5: %s\n", search(root, 5) ? "Found" : "Not found");
    printf("Search 25: %s\n", search(root, 25) ? "Found" : "Not found");

    // Print leaves (simplified)
    print_leaves(root);

    return 0;
}


