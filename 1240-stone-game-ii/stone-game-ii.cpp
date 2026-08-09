class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<int> suffix(n);
        partial_sum(piles.rbegin(), piles.rend(), suffix.rbegin());
        vector memo(n, vector<int>(n + 1));

        auto best = [&](this auto&& best, int i, int m) -> int {  // mover's max take from piles[i:]
            if (i + 2 * m >= n) return suffix[i];
            int& res = memo[i][m];
            if (!res) res = suffix[i] - ranges::min(views::iota(1, 2 * m + 1)
                          | views::transform([&](int x) { return best(i + x, max(m, x)); }));
            return res;
        };
        return best(0, 1);
    }
};