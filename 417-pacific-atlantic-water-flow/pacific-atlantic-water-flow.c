#include <stdlib.h>
#include <stdbool.h>

int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int** h, int m, int n, bool** visited, int r, int c) {
    visited[r][c] = true;
    for (int k = 0; k < 4; k++) {
        int nr = r + dirs[k][0];
        int nc = c + dirs[k][1];
        if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
            !visited[nr][nc] && h[nr][nc] >= h[r][c]) {
            dfs(h, m, n, visited, nr, nc);
        }
    }
}

int** pacificAtlantic(int** heights, int heightsSize, int* heightsColSize, int* returnSize, int** returnColumnSizes) {
    int m = heightsSize, n = heightsColSize[0];
    *returnSize = 0;
    
    bool** pacific = (bool**)malloc(m * sizeof(bool*));
    bool** atlantic = (bool**)malloc(m * sizeof(bool*));
    for (int i = 0; i < m; i++) {
        pacific[i] = (bool*)calloc(n, sizeof(bool));
        atlantic[i] = (bool*)calloc(n, sizeof(bool));
    }

    for (int i = 0; i < m; i++) {
        dfs(heights, m, n, pacific, i, 0);
        dfs(heights, m, n, atlantic, i, n-1);
    }
    for (int j = 0; j < n; j++) {
        dfs(heights, m, n, pacific, 0, j);
        dfs(heights, m, n, atlantic, m-1, j);
    }

    int maxCells = m * n;
    int** result = (int**)malloc(maxCells * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxCells * sizeof(int));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (pacific[i][j] && atlantic[i][j]) {
                result[*returnSize] = (int*)malloc(2 * sizeof(int));
                result[*returnSize][0] = i;
                result[*returnSize][1] = j;
                (*returnColumnSizes)[*returnSize] = 2;
                (*returnSize)++;
            }
        }
    }
    
    for (int i = 0; i < m; i++) {
        free(pacific[i]);
        free(atlantic[i]);
    }
    free(pacific);
    free(atlantic);
    
    return result;
}