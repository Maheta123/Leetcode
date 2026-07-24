class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;

        // Count frequency
        for (int num : nums)
            freq[num]++;

        vector<pair<int, int>> v;

        // Store {frequency, number}
        for (auto x : freq)
            v.push_back({x.second, x.first});

        // Sort in descending order
        sort(v.rbegin(), v.rend());

        vector<int> ans;

        // Take first k numbers
        for (int i = 0; i < k; i++)
            ans.push_back(v[i].second);

        return ans;
    }
};
