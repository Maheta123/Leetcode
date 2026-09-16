class Solution {
public:
    using ll=long long;
    ll mod=1e9+7;
    vector<ll>fact,ifact;
    ll fp(ll b,ll e){
        ll r=1;
        while(e){
            if(e&1)
                r=r*b%mod;
            b=b*b%mod;
            e>>=1;
        }
        return r;
    }
    int ncr(ll n,ll r){
        if(r<0||r>n)
            return 0;
        return fact[n]*ifact[r]%mod*ifact[n-r]%mod;
    }
    int numberOfSets(int n, int k) {
        int N=n+k+1;
        fact.resize(N+1),ifact.resize(N+1);
        fact[0]=1; 
        for(ll i=1;i<=N;++i)
            fact[i]=i*fact[i-1]%mod;
        for(ll i=0;i<=N;++i)
            ifact[i]=fp(fact[i],mod-2);
        return ncr(n+k-1,2*k);
    }
};