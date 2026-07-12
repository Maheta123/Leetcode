#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)

class Hasher {
    int64_t hash;  
    int64_t base; 
    int64_t mod;
    int64_t P;       
    int windowSz;
    
public:    
    Hasher(int64_t Base, int64_t Mod, int wz) : base(Base), mod(Mod), hash(0), windowSz(wz) {
        P = 1;
        for(int i = 0; i < windowSz - 1; ++i) {
            P = (P * base) % mod;
        }
    }

    void CalculateHash(const std::string &s) {
        hash = 0; 
        for(int i = 0; i < windowSz; ++i) {
            hash = (hash * base + s[i]) % mod;
        }
    }

    void Roll(char in, char out) {
        int64_t contri = (P * out) % mod;
        hash = (hash - contri + mod) % mod; 
        hash = (hash * base + in) % mod; 
    }
    
    void SetHash(int64_t hash) {
        this->hash = hash; 
    }

    int64_t GetHash() const {
        return hash;
    }
};

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if (unlikely(s.empty() || words.empty())) return {};

        int ws = words[0].size();
        int num_words = words.size();
        int total_len = ws * num_words;
        int n = s.length();
        
        if (unlikely(n < total_len)) return {};

        int64_t Mod = 1e9 + 7;
        int64_t Base = 31; 
        
        Hasher H(Base, Mod, ws);

        unordered_map<int64_t, int> target_counts;
        for (const auto& word : words) {
            H.CalculateHash(word);
            target_counts[H.GetHash()]++; 
        }

        vector<int64_t> s_hashes(n, -1);
        H.CalculateHash(s); 
        s_hashes[0] = H.GetHash();
        
        for(int i = 1; i <= n - ws; ++i) {
            H.Roll(s[i + ws - 1], s[i - 1]);
            s_hashes[i] = H.GetHash();
        }

        vector<int> ans;
        
        for (int i = 0; i < ws; ++i) {
            unordered_map<int64_t, int> window_counts; 
            int left = i;
            int count = 0;

            for (int right = i; right <= n - ws; right += ws) {
                int64_t curr_h = s_hashes[right];
                
                if (target_counts.find(curr_h) != target_counts.end()) {
                    window_counts[curr_h]++;
                    count++;
                    
                    while (unlikely(window_counts[curr_h] > target_counts[curr_h])) {
                        int64_t left_h = s_hashes[left];
                        window_counts[left_h]--;
                        count--;
                        left += ws;
                    }
                    
                    if (unlikely(count == num_words)) {
                        ans.push_back(left);
                    }
                } 
                else {
                    if (likely(count > 0)) { 
                        window_counts.clear();
                        count = 0;
                    }
                    left = right + ws;
                }
            }
        }
        
        return ans;
    }
};