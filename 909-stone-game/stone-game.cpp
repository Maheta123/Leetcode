class Solution {
public:
    int solveMem(vector<int> &piles,int i,vector<int> &dp)
    {
        if(i >= piles.size()) return 0;

        if(dp[i] != -1) return dp[i];

        int op1 = piles[i] + solveMem(piles,i+2,dp);

        int op2 = 0 + solveMem(piles,i+1,dp);

        int ans = max(op1,op2);

        dp[i] = ans;

        return dp[i];
    }
    int solveRec(vector<int> &piles,int i)
    {
        if(i >= piles.size()) return 0;

        int op1 = piles[i] + solveRec(piles,i+2);

        int op2 = 0 + solveRec(piles,i+1);

        int ans = max(op1,op2);

        return ans;
    }
    bool stoneGame(vector<int>& piles) {
        sort(piles.begin(),piles.end());

        int sum = 0;

        vector<int> dp(piles.size()+1,-1);

        for(auto i : piles) sum += i;

        int i = 0;
        int op1 = solveMem(piles,i,dp);

        cout<<op1;

        int op2 = sum - op1;

        return op1 > op2;
    }
};