class Solution {
public:
    string minWindow(string s, string t) {
        if (s.size() < t.size()) return "";

        int left = 0, count = 0;
        int best_left = 0, best_size = INT_MAX;

        unordered_map<char, int> target, window;

        for (char c : t)
            target[c]++;

        for (int right = 0; right < s.size(); right++) {

            window[s[right]]++;

            if (target.count(s[right]) &&
                window[s[right]] == target[s[right]]) {
                count++;
            }

            while (count == target.size()) {

                if (right - left + 1 < best_size) {
                    best_size = right - left + 1;
                    best_left = left;
                }

                window[s[left]]--;

                if (target.count(s[left]) &&
                    window[s[left]] < target[s[left]]) {
                    count--;
                }

                left++;
            }
        }

        return best_size == INT_MAX
            ? ""
            : s.substr(best_left, best_size);
    }
};