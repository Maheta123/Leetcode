class Solution {
public:
    int jump(vector<int>& nums) {
        int far =0, jumping=0, near=0;

        while(far < nums.size()-1){
                int farthest=0;
                for(int i=near; i<=far; i++){
                        farthest= max(farthest, i+nums[i]);
                }
                near=far;
                far= farthest;
                jumping++;
        }

        return jumping;
    }
};