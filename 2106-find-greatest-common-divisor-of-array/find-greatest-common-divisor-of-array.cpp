class Solution {
public:
    int calGcd(int a, int b){
        if(b == 0){
                return a;
        }
        return calGcd(b, a%b);
    }
    int findGCD(vector<int>& nums) {
        int mn = 1001 , mx=0;

        for(int i=0; i<nums.size(); i++){
            if(nums[i]<mn) mn = nums[i];
            if(nums[i] > mx) mx = nums[i];
        }

        return calGcd(mn,mx);
    }
};