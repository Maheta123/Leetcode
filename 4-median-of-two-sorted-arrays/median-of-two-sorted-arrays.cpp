class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        int n1= nums1.size();
        int n2 =nums2.size();

        int k = n1 +n2;
        vector<int> num3;

        for(int i=0; i< n1; i++){
                num3.push_back(nums1[i]);
        }
                
        for(int i=0; i< n2; i++){
                num3.push_back(nums2[i]);
        }

        sort(num3.begin(), num3.end());

        if(k%2 == 1){
                return  num3[k/2];
        }

        return (num3[k/2] + num3[(k/2)-1] )/2.0;
         
    }
};