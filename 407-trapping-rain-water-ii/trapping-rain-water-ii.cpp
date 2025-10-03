#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& mat) {
        int n = mat.size();
        if (n == 0) return 0;
        int m = mat[0].size();
        if (m == 0) return 0;

        // Min-heap: stores {height, {x, y}}
        priority_queue<
            pair<int, pair<int, int>>,
            vector<pair<int, pair<int, int>>>,
            greater<pair<int, pair<int, int>>>
        > pq;

        vector<vector<bool>> vis(n, vector<bool>(m, false));

        // Push all boundary cells into the heap
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                    pq.push({mat[i][j], {i, j}});
                    vis[i][j] = true;
                }
            }
        }

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int ans = 0;

        while (!pq.empty()) {
            auto [height, coord] = pq.top();
            pq.pop();
            int x = coord.first;
            int y = coord.second;

            for (auto [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && ny >= 0 && nx < n && ny < m && !vis[nx][ny]) {
                    vis[nx][ny] = true;
                    ans += max(0, height - mat[nx][ny]);
                    pq.push({max(height, mat[nx][ny]), {nx, ny}});
                }
            }
        }

        return ans;
    }
};
