// Time complexity : O(s.size())
// Space complexity : O(1)

class Solution {
public:
    bool
    isAcronym(vector<string>& words, string s) {
        if (s.size() != words.size()) {
            // Num words and string size differ => 's' is not an acronyr
            return false;
        }
        
        // Iterate over each word sequentially
        auto sChrIdx = 0;
        for (auto & word : words) {
            // Compare first char in word with string char at appropriate index
            if (s[sChrIdx++] != word[0]) {
                return false;
            }
        }
        
        return true;
    }
};
