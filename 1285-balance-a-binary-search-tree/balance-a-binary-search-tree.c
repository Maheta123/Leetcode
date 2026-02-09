/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * struct TreeNode *left;
 * struct TreeNode *right;
 * };
 */
#include <stdlib.h>

int count(struct TreeNode* root) {
    if (!root) {
        return 0;
    }
    return 1 + count(root -> left) + count(root -> right);
}

void inorder(struct TreeNode* root, struct TreeNode** arr, int* index) {
    if (!root) {
        return;
    }
    inorder(root -> left, arr, index);
    arr[(*index)++] = root;
    inorder(root -> right, arr, index);
}

struct TreeNode* build(struct TreeNode** arr, int l, int r) {
    if (l > r) {
        return NULL;
    }

    int m = l + (r - l) / 2;
    struct TreeNode* node = arr[m];

    node -> left = build(arr, l, m - 1);
    node -> right = build(arr, m + 1, r);

    return node;
}

struct TreeNode* balanceBST(struct TreeNode* root) {
    if (!root) {
        return NULL;
    }

    int n = count(root);
    
    struct TreeNode** nodes = (struct TreeNode**)malloc(n * sizeof(struct TreeNode*));
    int index = 0;
    
    inorder(root, nodes, &index);
    
    struct TreeNode* res = build(nodes, 0, n - 1);
    
    free(nodes);
    
    return res;
}