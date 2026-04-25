#include <stdio.h>
#include <stdlib.h>

int cmpLongLong(const void* a, const void* b) {
    long long valA = *(long long*)a;
    long long valB = *(long long*)b;
    if (valA < valB) return -1;
    else if (valA > valB) return 1;
    else return 0;
}

int canPlace(long long d, int k, int n, long long* ext, long long L) {
    for (int start = 0; start < n; start++) {
        int cur = start;
        long long last = ext[start];
        int valid = 1;
        int limit = start + n;
        for (int step = 1; step < k; step++) {
            long long target = last + d;
            int lo = cur + 1, hi = limit;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (ext[mid] < target)
                    lo = mid + 1;
                else
                    hi = mid;
            }
            if (lo == limit) {
                valid = 0;
                break;
            }
            cur = lo;
            last = ext[cur];
        }
        if (valid && (ext[start] + L - last >= d))
            return 1;
    }
    return 0;
}

int maxDistance(int side, int** points, int pointsSize, int* pointsColSize, int k) {
    int n = pointsSize;
    long long* pos = (long long*) malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        int x = points[i][0], y = points[i][1];
        long long p;
        if (y == 0) {
            p = x;
        } else if (x == side) {
            p = side + y;
        } else if (y == side) {
            p = 2LL * side + (side - x);
        } else {
            p = 3LL * side + (side - y);
        }
        pos[i] = p;
    }
    qsort(pos, n, sizeof(long long), cmpLongLong);
    
    long long L = 4LL * side;
    int total = n * 2;
    long long* ext = (long long*) malloc(total * sizeof(long long));
    for (int i = 0; i < n; i++) {
        ext[i] = pos[i];
        ext[i+n] = pos[i] + L;
    }
    
    long long low = 0, high = 2LL * side;
    while (low < high) {
        long long mid = (low + high + 1) / 2;
        if (canPlace(mid, k, n, ext, L))
            low = mid;
        else
            high = mid - 1;
    }
    
    free(pos);
    free(ext);
    return (int) low;
}