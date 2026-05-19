class Solution {
public:
    int lengthOfLastWord(string s) {
            int len =0;
            int space=0;
            
            for(int i=s.size()-1; i>=0; i--){
                    if(s[i] == ' '){
                        space++;
                        if(len > 0){
                            break;
                        }
                        
                    }else{
                        len++;
                    }
            }

            return len;
    }
};