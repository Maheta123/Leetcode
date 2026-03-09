class Solution 
{
private:
    int m_limit;
    const int MOD = 1e9 + 7;
    vector<vector<vector<int>>> dp;
public:
    int numberOfStableArrays(int zero, int one, int limit) 
    {
        m_limit = limit;
       
        // SOL-2: MEMOIZATION DP -- TOP DOWN DP.
        dp = vector<vector<vector<int>>>(zero+1, vector<vector<int>>(one+1, vector<int>(3, -1)));
        return memo(zero, one, -1) % MOD;        
    }

private:
    // SOL-2: MEMOIZATION -- TOP DOWN DP
    int memo(int zero, int one, int prev)
    {
        if ( zero == 0 && one == 0 )
            return 1;
        
        if ( zero < 0 || one < 0 )
            return 0;
        
        if ( dp[zero][one][prev+1] != -1 )
            return dp[zero][one][prev+1];

        int ans = 0;
        for ( int i=1; i<=m_limit; i++ )
        {
            if ( prev == -1 || prev == 0 )
                ans = (ans + memo(zero, one-i, 1)) % MOD;
            if ( prev == -1 || prev == 1 )
                ans = (ans + memo(zero-i, one, 0)) % MOD;
        }
        return dp[zero][one][prev+1] = ans % MOD;
    }
};