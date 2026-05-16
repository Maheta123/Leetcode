class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int max_pro=0, best_buy=prices[0];

        for(int i=0;i<prices.size();i++){
                if(prices[i] >best_buy){
                    max_pro = max(max_pro, prices[i]- best_buy);
                }
                best_buy= min(best_buy,prices[i]);
        }
        
        return max_pro;
    }
};