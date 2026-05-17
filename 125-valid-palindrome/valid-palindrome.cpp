class Solution {
public:

    bool isPalindrome(string s) {
        int l=0,n =s.length()-1;

        while(l <=n){
                if( !isalnum(s[n])){
                    n--; continue;
                }
                if( !isalnum(s[l])){
                    l++; continue;
                }
                if( tolower(s[l]) != tolower(s[n]) ){
                        return false;
                }

                l++;
                n--;
        }

        return true;
    }
};