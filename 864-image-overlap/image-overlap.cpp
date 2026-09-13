class Solution {
public:
    int getAns(vector<vector<int>>& img1, vector<vector<int>>& img2){
        int n = img1.size() , m = img2.size() ; 
        int ans = 0 ; 
        for(int i = 0 ; i<n ; i++){
            for(int j = 0 ; j<m ; j++){
                int START_I = i , START_J = j ; 
                int cnt = 0 ; 
                for(int _i = 0 , si = START_I ; si<n ; si++ , _i++){
                    for(int _j = 0, sj = START_J ; sj<m; sj++ , _j++){
                        if(img2[si][sj] and img1[_i][_j]) cnt++ ; 
                    }
                }
                ans = max(ans , cnt) ; 
            }
        }  
        return ans ; 
    }
    void reverseCols(vector<vector<int>>& img){
        for(auto& row : img) reverse(row.begin() , row.end()) ; 
    }
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int ans = max(getAns(img1 , img2) , getAns(img2, img1)) ;
        reverseCols(img1) ; reverseCols(img2) ; 
        ans = max({ans , getAns(img1 , img2) , getAns(img2 , img1)}); 
        return ans ; 
    }

};