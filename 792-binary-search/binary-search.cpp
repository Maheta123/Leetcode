class Solution {
public:
    int fibo(vector<int>& nums, int target, int st, int end){
            if(st <= end){
                   
                int mid = st + (end-st)  /2;

                if(nums[mid] == target){
                        return mid;
                }
                else if( target >= nums[mid]){
                        return fibo(nums, target, mid+1 ,end);
                }else{
                        return fibo(nums, target, st ,mid-1);
                }
            
            
            }

             return -1;
    }
    int search(vector<int>& nums, int target) {
            return fibo(nums,target,0,nums.size()-1);
    }
};