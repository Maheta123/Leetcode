class Solution {
public:

    bool isVow(char ch){
            ch = tolower(ch);
            if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'){
                return true;
            }
            return false;
    }
    string sortVowels(string s) {
        vector<char> v;

        for (char c : s)
                if(isVow(c)) v.push_back(c);

        sort(v.begin(), v.end());
        int j=0;
        for(char &c : s){
                if(isVow(c)){
                        c = v[j++];
                }
        }

        return s;
    }
};