class Solution {
public:
    int maxProduct(int n) {
        if (n==0) return 0;
        n= abs(n);

        vector<int> digits;
        int ans=1;
        while(n > 0){
                digits.push_back(n%10);
                n /= 10;
        }

        sort(digits.begin(), digits.end());
        return digits[digits.size() - 1] * digits[digits.size() - 2];;
    }
};