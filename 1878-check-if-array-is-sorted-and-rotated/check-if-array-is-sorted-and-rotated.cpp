class Solution {
public:
    bool check(vector<int>& nums) {
        int n= nums.size();
        bool fault = 0;

        for(int i=0; i< n; i++){
            if(nums[i] > nums[(i+1) %n] && exchange(fault,1) )  {
                    return 0;
            }
        }

        return 1;
    }
};