class Solution {
public:
    void merge(vector<int>& nums, int st,int mid, int end){
            int i=st,j=mid+1;
            vector<int> temp;

            while(i<=mid && j<=end){
                    if(nums[i] < nums[j]){
                           temp.push_back(nums[i]); 
                           i++;
                    }else{
                        temp.push_back(nums[j]); 
                           j++;
                    }
    
            }


            while(i<=mid ){
                    temp.push_back(nums[i]); 
                    i++;
            }

            while(j<=end){
                    temp.push_back(nums[j]); 
                    j++;  
            }

            for(int i=st;i<=end;i++){
                    nums[i] = temp[i-st];
            }
    }

    void merge_short(vector<int>& nums, int st,int end){
            if (st >= end){
                    return;
            }
            int mid = st + (end-st)/2;
            merge_short(nums,st,mid);
            merge_short(nums,mid+1,end);
            merge(nums,st,mid,end);
    }


    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size()-1;
        
        merge_short(nums,0,n);

        return nums;
    }
};