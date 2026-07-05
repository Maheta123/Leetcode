class Solution {
public:
    int isSquare(int n){
        int sum=0;
        while(n){
            int rem =n%10;
            sum += rem*rem;
            n = n/10;
        }
        return sum;
    }
    bool isHappy(int n) {
        unordered_set<int> st;

        while(true  ){
                if(n==1) return true;
                n= isSquare(n);

                if(st.count(n) ==1){
                    return false;
                }
                st.insert(n);
        }
    }
};