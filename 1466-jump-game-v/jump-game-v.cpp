class Solution 
{
    public:
    void steps(vector<int>& dp, vector<int>& v, int i, int d)
    {
        int n=v.size();
        if(dp[i]!=-1) return;
        if((i+1<n&&v[i+1]>=v[i]&&i-1>=0&&v[i-1]>=v[i])||(i==n-1&&v[i-1]>=v[i])||(i==0&&v[i+1]>=v[i]))
        {
            dp[i]=0;
            return;
        }
        int ans=0;
        for(int j=i+1;j<=min(n-1,i+d);j++)
        {
            if(v[j]<v[i])
            {   
                if(dp[j]==-1) steps(dp,v,j,d);
                ans=max(ans,dp[j]+1);
            }
            else break;
        }
        for(int j=i-1;j>=max(0,i-d);j--)
        {
            if(v[j]<v[i])
            {
                steps(dp,v,j,d);
                ans=max(ans,dp[j]+1);
            }
            else break;
        }
        dp[i]=ans;
        return;
    }
    int maxJumps(vector<int>& v, int d) 
    {
        int n=v.size();
        if(n==1) return 1;
        vector<int> dp(n,-1);
        for(int i=0;i<n;i++)
        {
            steps(dp,v,i,d);
        }
        return *max_element(dp.begin(),dp.end())+1;
    }
};