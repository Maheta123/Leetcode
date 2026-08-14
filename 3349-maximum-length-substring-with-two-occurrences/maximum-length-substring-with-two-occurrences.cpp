class Solution {
public:
    int maximumLengthSubstring(string s) {
        
        unordered_map<char,int> mp;
        int maxlength=0;
        int left=0;
        for(int i=0; i<s.size(); i++){
                mp[s[i]]++;
                while( mp[s[i]] > 2){
                                mp[s[left]]--;
                                left++;    
                }
                
                maxlength = max(maxlength, i-left+1);
        }
        return maxlength;
    }
};