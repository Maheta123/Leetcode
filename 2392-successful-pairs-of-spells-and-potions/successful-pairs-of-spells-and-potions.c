#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int goodPairs(int* potions, int potionsSize, long long threshold) {
    int left = 0, right = potionsSize;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if ((long long)potions[mid] >= threshold) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return potionsSize - left;
}

int* successfulPairs(int* spells, int spellsSize, int* potions, int potionsSize, long long success, int* returnSize) {
    int* ans = (int*)malloc(sizeof(int) * spellsSize);
    *returnSize = spellsSize;

    qsort(potions, potionsSize, sizeof(int), cmp);

    for (int i = 0; i < spellsSize; ++i) {
        long long threshold = (success + spells[i] - 1) / spells[i];
        ans[i] = goodPairs(potions, potionsSize, threshold);
    }

    return ans;
}