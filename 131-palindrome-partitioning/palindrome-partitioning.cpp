class Solution {
public:
    bool ispalin(string s){
        string s2=s;
        reverse(s2.begin(),s2.end() );

        return s == s2;
    }
    
    void getallpartition(string s,vector<vector<string>>& ans, vector<string>& partision){
            if(s.size() == 0){
                ans.push_back(partision);
            }

            for(int i=0; i< s.size() ; i++){
                    string part= s.substr(0,i+1);
                    if(ispalin(part)){
                            partision.push_back(part);
                            getallpartition(s.substr(i+1), ans,partision );
                            partision.pop_back();

                    }
            }
    }

    vector<vector<string>> partition(string s) {
         vector<vector<string>> ans;
         vector<string> partision;

         getallpartition(s,ans,partision);

         return ans;
    }
};