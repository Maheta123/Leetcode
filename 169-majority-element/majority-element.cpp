class Solution {
public:
    int majorityElement(vector<int>& nums) {
       int n = nums.size();
       int freq = 1;
       int ans = nums[0];

        for(int i=1;i<n;i++){
            if (freq ==0) {
                ans = nums[i];
            }
            if (ans==nums[i]){
                freq++;
            }else{
                freq--;
            }
        }
        return ans;
    }
};