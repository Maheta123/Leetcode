#include <stdio.h>
#include <limits.h>

int minScoreTriangulation(int* values, int valuesSize) {
    int n = valuesSize;
    int dp[50][50] = {0}; 

    for (int len = 2; len < n; len++) {
        for (int i = 0; i + len < n; i++) {
            int j = i + len;
            dp[i][j] = INT_MAX;
            for (int k = i + 1; k < j; k++) {
                int score = dp[i][k] + dp[k][j] + values[i] * values[j] * values[k];
                if (score < dp[i][j]) dp[i][j] = score;
            }
        }
    }
    return dp[0][n - 1];
}