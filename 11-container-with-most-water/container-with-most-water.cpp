class Solution {
public:
    int maxArea(vector<int>& height) {
        int max_water=0;
        int i=0;
        int j=height.size()-1;

        while( i<j){
                    int w = j-i;
                    int area = min(height[i],height[j]);
                    int current = area*w;
                    max_water = max(max_water, current);
                    
                    if(height[i]<height[j]){
                            i++;
                    }else{
                            j--;
                    }
        }
        return max_water;
    }
};