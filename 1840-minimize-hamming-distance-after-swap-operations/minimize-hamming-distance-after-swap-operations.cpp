class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        vector<pair<int, int>> R;
        R.reserve(restrictions.size() + 1);
        R.emplace_back(1, 0);
        for (auto &r : restrictions) R.emplace_back(r[0], r[1]);
        sort(R.begin(), R.end());
        const int N = R.size();
        // find the real restrictions, first forward, than backward.
        for (int i = 0; i < N - 1; i++) {
            R[i+1].second = min(R[i+1].second, R[i].second + (R[i+1].first - R[i].first));
        }
        for (int i = N - 1; i >= 1; i--) {
            R[i-1].second = min(R[i-1].second, R[i].second + (R[i].first - R[i-1].first));
        }

        // what is the largest building at the end?
        int ans = R.back().second + (n - R.back().first);

        // now all the in-betweens

        for (int i = 0; i < N - 1; i++) {
            //(x1, y1), (x2, y2)
            // y1 + (x - x1) = y2 + (x2 - x)
            // x = (y2 + x2 - y1 + x1) / 2 -- needs long long
            long long x1 = R[i].first, y1 = R[i].second;
            long long x2 = R[i+1].first, y2 = R[i+1].second;

            long long x = (y2 + x2 - y1 + x1) / 2;

            ans = max(ans, (int)(y1 + (x - x1)));
        }
        return ans;
    }
};
