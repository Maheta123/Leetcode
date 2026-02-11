#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int min_val;
    int max_val;
    int lazy;
} Node;

Node* tree;
int tree_size;

void push(int node) {
    if (tree[node].lazy != 0) {
        int l = 2 * node;
        int r = 2 * node + 1;
        int lazy = tree[node].lazy;

        tree[l].lazy += lazy;
        tree[l].min_val += lazy;
        tree[l].max_val += lazy;

        tree[r].lazy += lazy;
        tree[r].min_val += lazy;
        tree[r].max_val += lazy;

        tree[node].lazy = 0;
    }
}

void update(int node, int st, int en, int l, int r, int val) {
    if (l > en || r < st) {
        return;
    }
    if (l <= st && en <= r) {
        tree[node].lazy += val;
        tree[node].min_val += val;
        tree[node].max_val += val;
        return;
    }
    push(node);
    int m = (st + en) / 2;
    update(2 * node, st, m, l, r, val);
    update(2 * node + 1, m + 1, en, l, r, val);
    tree[node].min_val = fmin(tree[2 * node].min_val, tree[2 * node + 1].min_val);
    tree[node].max_val = fmax(tree[2 * node].max_val, tree[2 * node + 1].max_val);
}

int findFirstZero(int node, int st, int en, int lim) {
    if (tree[node].min_val > 0 || tree[node].max_val < 0) {
        return -1;
    }
    if (st > lim) {
        return -1;
    }

    if (st == en) {
        return (tree[node].min_val == 0) ? st : -1;
    }

    push(node);
    int m = (st + en) / 2;

    int res = findFirstZero(2 * node, st, m, lim);
    if (res != -1) {
        return res;
    }

    return findFirstZero(2 * node + 1, m + 1, en, lim);
}

int longestBalanced(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }
    
    tree_size = 4 * numsSize;
    tree = (Node*)calloc(tree_size, sizeof(Node));
    
    int* pos = (int*)malloc(100005 * sizeof(int));
    for(int i = 0; i < 100005; i++) {
        pos[i] = -1;
    }
    
    int max_len = 0;

    for (int i = 0; i < numsSize; ++i) {
        int val = nums[i];
        int pre = pos[val];
        int ch = (val % 2 == 0) ? 1 : -1;

        update(1, 0, numsSize - 1, pre + 1, i, ch);
        pos[val] = i;

        int l = findFirstZero(1, 0, numsSize - 1, i);
        if (l != -1) {
            max_len = fmax(max_len, i - l + 1);
        }
    }

    free(tree);
    free(pos);
    return max_len;
}