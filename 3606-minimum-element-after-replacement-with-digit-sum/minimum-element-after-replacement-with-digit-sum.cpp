class Solution {
public:
    int minElement(vector<int>& nums) {

        int ans=INT_MAX;

        for(int i=0;i< nums.size(); i++){
                int temp=0;
                int x= nums[i];
                while( x > 0){
                        int deigit = x%10;
                        temp += deigit;
                        x /=10;
                }

                ans = min(ans,temp);
        }
     return ans;   
    }
};