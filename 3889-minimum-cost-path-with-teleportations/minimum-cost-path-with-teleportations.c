#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minCost(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize;
    int n = gridColSize[0];
    
    int total = (k + 1) * m * n;
    int* dp = (int*)malloc(total * sizeof(int));
    
    for (int i = 0; i < total; i++) {
        dp[i] = INT_MAX;
    }
    
    dp[0] = 0;
    
    int* min_cost = (int*)malloc(10002 * sizeof(int));
    
    for (int t = 0; t <= k; t++) {
        int offset = t * m * n;
        
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                int curr_ind = offset + r * n + c;
                if (dp[curr_ind] == INT_MAX) {
                    continue;
                }
                
                int curr_cost = dp[curr_ind];
                
                if (r + 1 < m) {
                    int down_ind = offset + (r + 1) * n + c;
                    long long next = (long long)curr_cost + grid[r + 1][c];
                    if (next < dp[down_ind]) dp[down_ind] = (int)next;
                }
                
                if (c + 1 < n) {
                    int right_ind = offset + r * n + (c + 1);
                    long long next = (long long)curr_cost + grid[r][c + 1];
                    if (next < dp[right_ind]) {
                        dp[right_ind] = (int)next;
                    }
                }
            }
        }
        
        if (t < k) {
            for (int i = 0; i < 10002; i++) {
                min_cost[i] = INT_MAX;
            }
            
            for (int r = 0; r < m; r++) {
                for (int c = 0; c < n; c++) {
                    int idx = offset + r * n + c;
                    if (dp[idx] != INT_MAX) {
                        int val = grid[r][c];
                        if (dp[idx] < min_cost[val]) {
                            min_cost[val] = dp[idx];
                        }
                    }
                }
            }
            
            int curr_min = INT_MAX;
            for (int v = 10000; v >= 0; v--) {
                if (min_cost[v] < curr_min) {
                    curr_min = min_cost[v];
                } else {
                    min_cost[v] = curr_min;
                }
            }
            
            int next = (t + 1) * m * n;
            for (int r = 0; r < m; r++) {
                for (int c = 0; c < n; c++) {
                    int val = grid[r][c];
                    int idx = next + r * n + c;
                    if (min_cost[val] < dp[idx]) {
                        dp[idx] = min_cost[val];
                    }
                }
            }
        }
    }
    
    int ans = INT_MAX;
    int ind = (m - 1) * n + (n - 1);
    for (int t = 0; t <= k; t++) {
        int idx = t * m * n + ind;
        ans = fmin(ans, dp[idx]);
    }
    
    free(dp);
    free(min_cost);
    return ans;
}