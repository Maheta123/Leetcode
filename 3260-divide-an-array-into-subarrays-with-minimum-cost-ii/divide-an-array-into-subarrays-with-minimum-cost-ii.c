typedef long long ll;

static int cmpInt(const void* a, const void* b){
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

static void bitAdd(ll* bit, int n, int idx, ll delta){
    for (; idx <= n; idx += idx & -idx) 
        bit[idx] += delta;
}
static ll bitSum(ll* bit, int idx){
    ll s = 0;
    for (; idx > 0; idx -= idx & -idx) 
        s += bit[idx];
    return s;
}

static int bitKth(ll* bitCnt, int n, ll k){
    int idx = 0;
    int step = 1;
    while ((step << 1) <= n) 
        step <<= 1;

    for (; step > 0; step >>= 1){
        int nxt = idx + step;
        if (nxt <= n && bitCnt[nxt] < k){
            idx = nxt;
            k -= bitCnt[nxt];
        }
    }
    return idx + 1;
}

static ll sumKSmallest(ll* bitCnt, ll* bitSumArr, int* vals, int m, int k){
    if (k <= 0) 
        return 0;
    int idx = bitKth(bitCnt, m, (ll)k);         
    ll cntLess = bitSum(bitCnt, idx - 1);
    ll sumLess = bitSum(bitSumArr, idx - 1);
    ll need = (ll)k - cntLess;
    ll v = (ll)vals[idx - 1];                   

    return sumLess + need * v;
}

static int lowerBound(int* vals, int m, int x){
    int l = 0, r = m;
    while (l < r){
        int mid = (l + r) >> 1;
        if (vals[mid] < x) 
            l = mid + 1;
        else r = mid;
    }
    return l;
}

long long minimumCost(int* nums, int numsSize, int k, int dist) {
    ll base = (ll)nums[0];
    int kSmall = k - 1;             
    if (kSmall <= 0) 
        return base;

    int aSize = numsSize - 1;
    int* a = nums + 1;

    int winSize = dist + 1;
    if (winSize > aSize) 
        return -1;

    int* vals = (int*)malloc(sizeof(int) * aSize);
    memcpy(vals, a, sizeof(int) * aSize);
    qsort(vals, aSize, sizeof(int), cmpInt);

    int m = 0;
    for (int i = 0; i < aSize; i++){
        if (i == 0 || vals[i] != vals[i - 1]){
            vals[m++] = vals[i];
        }
    }

    ll* bitCnt = (ll*)calloc(m + 1, sizeof(ll));
    ll* bitSumArr = (ll*)calloc(m + 1, sizeof(ll));


    for (int i = 0; i < winSize; i++){
        int pos = lowerBound(vals, m, a[i]) + 1;    
        bitAdd(bitCnt, m, pos, 1);
        bitAdd(bitSumArr, m, pos, (ll)a[i]);
    }

    ll res = LLONG_MAX;

    for (int l = 0; l + dist < aSize; l++){
        ll sumSmall = sumKSmallest(bitCnt, bitSumArr, vals, m, kSmall);
        ll cur = base + sumSmall;
        if (cur < res) 
            res = cur;

        if (l + dist + 1 >= aSize) 
            break;
        int out = a[l];
        int in  = a[l + dist + 1];
        int posOut = lowerBound(vals, m, out) + 1;
        int posIn  = lowerBound(vals, m, in) + 1;
        bitAdd(bitCnt, m, posOut, -1);
        bitAdd(bitSumArr, m, posOut, -(ll)out);
        bitAdd(bitCnt, m, posIn, 1);
        bitAdd(bitSumArr, m, posIn, (ll)in);
    }

    free(vals);
    free(bitCnt);
    free(bitSumArr);

    return res;
}