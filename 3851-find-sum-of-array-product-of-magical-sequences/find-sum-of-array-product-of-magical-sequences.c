#define MOD 1000000007

// Helper popcount for nonnegative small integers
static int popcount_int(int x) {
    int cnt = 0;
    while (x) {
        x &= (x - 1);
        cnt++;
    }
    return cnt;
}

int magicalSum(int m, int k, const int* nums, int n) {
    // Precompute powtab[i][c] = nums[i]^c mod MOD for c in [0..m]
    int** powtab = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        powtab[i] = (int*)malloc((m + 1) * sizeof(int));
        powtab[i][0] = 1;
        for (int c = 1; c <= m; c++) {
            long long v = (1LL * powtab[i][c - 1] * nums[i]) % MOD;
            powtab[i][c] = (int)v;
        }
    }

    // Precompute combinations comb[r][c] = C(r, c) mod MOD for r,c in [0..m]
    int** comb = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i <= m; i++) {
        comb[i] = (int*)malloc((m + 1) * sizeof(int));
        memset(comb[i], 0, (m + 1) * sizeof(int));
    }
    for (int i = 0; i <= m; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
            if (comb[i][j] >= MOD) comb[i][j] -= MOD;
        }
    }

    // dp[rem][carry][ones] holds the running total after processing some prefix of indices:
    // rem picks left to place, current carry value, ones bits produced so far
    int ***dp = (int***)malloc((m + 1) * sizeof(int**));
    int ***next = (int***)malloc((m + 1) * sizeof(int**));
    for (int rem = 0; rem <= m; rem++) {
        dp[rem] = (int**)malloc((m + 1) * sizeof(int*));
        next[rem] = (int**)malloc((m + 1) * sizeof(int*));
        for (int carry = 0; carry <= m; carry++) {
            dp[rem][carry] = (int*)calloc(k + 1, sizeof(int));
            next[rem][carry] = (int*)calloc(k + 1, sizeof(int));
        }
    }
    dp[m][0][0] = 1; // start with all m picks remaining, carry = 0, ones = 0

    for (int i = 0; i < n; i++) {
        // clear next
        for (int rem = 0; rem <= m; rem++) {
            for (int carry = 0; carry <= m; carry++) {
                memset(next[rem][carry], 0, (k + 1) * sizeof(int));
            }
        }

        for (int rem = 0; rem <= m; rem++) {
            for (int carry = 0; carry <= m; carry++) {
                for (int ones = 0; ones <= k; ones++) {
                    int base = dp[rem][carry][ones];
                    if (base == 0) continue;
                    // Choose c copies of index i among the rem remaining positions
                    for (int c = 0; c <= rem; c++) {
                        int t = c + carry;       // add c to current bit with carry in
                        int bit = t & 1;         // output bit at this position
                        int ones2 = ones + bit;  // update ones count
                        if (ones2 > k) continue;
                        int carry2 = t >> 1;     // carry to the next bit
                        int rem2 = rem - c;

                        // Transition weight = comb[rem][c] (ways to place c copies) * nums[i]^c
                        long long add = base;
                        add = (add * comb[rem][c]) % MOD;
                        add = (add * powtab[i][c]) % MOD;

                        int cur = next[rem2][carry2][ones2] + (int)add;
                        if (cur >= MOD) cur -= MOD;
                        next[rem2][carry2][ones2] = cur;
                    }
                }
            }
        }

        // swap dp and next
        int*** tmp = dp;
        dp = next;
        next = tmp;
    }

    // Finish: only states with rem = 0 are valid
    // Leftover carry still contributes popcount(carry) ones
    long long ans = 0;
    for (int carry = 0; carry <= m; carry++) {
        int extra = popcount_int(carry);
        int need = k - extra;
        if (need >= 0 && need <= k) {
            ans += dp[0][carry][need];
            if (ans >= MOD) ans -= MOD;
        }
    }

    // free memory
    for (int i = 0; i < n; i++) free(powtab[i]);
    free(powtab);
    for (int i = 0; i <= m; i++) free(comb[i]);
    free(comb);
    for (int rem = 0; rem <= m; rem++) {
        for (int carry = 0; carry <= m; carry++) {
            free(dp[rem][carry]);
            free(next[rem][carry]);
        }
        free(dp[rem]);
        free(next[rem]);
    }
    free(dp);
    free(next);

    return (int)(ans % MOD);
}