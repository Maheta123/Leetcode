#pragma GCC optimize("O3, unroll-loops")
int minNumberOperations(int* target, int n) {
    int ans=target[0];
    for(int i=1; i<n; i++){
        ans+=fmax(target[i]-target[i-1], 0);
    }
    return ans;
}