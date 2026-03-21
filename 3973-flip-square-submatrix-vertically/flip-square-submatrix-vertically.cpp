class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        int lastCol = y + k, lastRow = x + k - 1, n = k/2;

        for(int i=0;i<n;++i){
            for(int j = y;j<lastCol;++j){
                int temp = grid[x+i][j];
                grid[x+i][j] = grid[lastRow - i][j];
                grid[lastRow - i][j] = temp;
            }
        }

        return grid;
    }
};