class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int v) {
    int m[100001] = {}, sz = nums.size();
    for (auto n : nums)
        // C++ fix for negative remainder: (b + (a % b)) % b
        ++m[(v + n % v) % v];
    int i = min_element(begin(m), begin(m) + v) - begin(m);
    return i + m[i] * v;
}
};