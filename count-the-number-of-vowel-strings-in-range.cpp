class Solution {
public:
    int
    vowelStrings(vector<string>& words, int left, int right) {
        if (words.empty()) {
            return 0;
        }
        
        left = max(0, left);
        right = min(right, int(words.size() - 1));
        
        int nWordCnt = 0;
        // Iterate over the inclusive range
        for (int i = left; i <= right; ++i) {
            // Current word
            auto & w = words[i];
            if (isVowel(w[0]) && isVowel(w[w.size() - 1])) {
                ++nWordCnt;
            }
        }
        
        return nWordCnt;
    }
    
private:
    
    inline bool
    isVowel(char c) {
        return ('a' == c) || ('e' == c) || ('i' == c) || ('o' == c) || ('u' == c);
    }
};
