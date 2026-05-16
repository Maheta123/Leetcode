class Solution {
public:
    int findMin(vector<int>& nums) {
        int ans=INT_MAX;
        for(int i: nums){
            if(i < ans){
                ans=i;
            }
        }

        return ans;
        
    }
};