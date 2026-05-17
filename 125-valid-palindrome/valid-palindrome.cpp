class Solution {
public:
    bool isAlplaNumaric(char ch){
            if( (ch>='0' && ch<='9')   ||  ( tolower(ch)>='a' && tolower(ch)<='z' )  ){
                    return true;
            }
        return false;
    }

    bool isPalindrome(string s) {
        int l=0,n =s.length()-1;

        while(l <=n){
                if( !isAlplaNumaric(s[n])){
                    n--; continue;
                }
                if( !isAlplaNumaric(s[l])){
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