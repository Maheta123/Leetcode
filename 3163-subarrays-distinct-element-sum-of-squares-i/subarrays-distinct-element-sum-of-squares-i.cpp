class Solution {
private:
    int n;
    int countDistinct(int idx, vector<int> &nums){
        unordered_map<int, int> mp;
        int sol = 0;
        for(;idx<n;idx++){
            mp[nums[idx]]++;
            sol += (mp.size() * mp.size());
        }
        return sol;
    }
public:
    int sumCounts(vector<int>& nums) {
        long long int sol = 0;
        n = nums.size();
        for(int i = 0; i< n;i++){
            sol += countDistinct(i, nums);
        }
        return sol;
    }
};