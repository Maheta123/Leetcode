class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
    long long dp[100001] = {0}, max_dp = 0;
    sort(begin(power), end(power));
    for (int i = 0, j = 0; i < power.size(); ++i)        
        if (power[i] == power[max(0, i - 1)])
            dp[i + 1] = power[i] + dp[i];
        else {
            while(power[j] + 2 < power[i])
                max_dp = max(max_dp, dp[++j]);
            dp[i + 1] = power[i] + max_dp;
        }
    return *max_element(begin(dp), begin(dp) + power.size() + 1);
}
};