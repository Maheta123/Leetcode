class Solution {
public:
    int getCommon(vector<int>& n1, vector<int>& n2) {
        sort(n1.begin(),n1.end());
        sort(n2.begin(),n2.end());

        int i=0,j=0;

        while(i < n1.size() && j<n2.size()){
                if(n1[i] == n2[j]){
                        return n1[i];
                }
                else if(n1[i] < n2[j]){
                        i++;
                }else{
                        j++;
                }
        }

    return -1;

        
    }
};