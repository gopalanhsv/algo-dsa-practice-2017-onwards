// n => words.size()
// A => average word length of a string in 'words'
// Time Complexity : O((n ^ 2)A)
// Space Complexity : O(1)

class Solution {
public:
    int
    countPrefixSuffixPairs(vector<string>& words) {
        auto arrLen = words.size();
        auto nPairs = 0;
        for (auto i = 0; i < arrLen; ++i) {
            for (auto j = i + 1; j < arrLen; ++j) {
                if (isPrefixAndSuffixSame(words[i], words[j])) {
                    ++nPairs;
                }
            }
        }
        return nPairs;
    }

private:
    bool
    isPrefixAndSuffixSame(const string& s1, const string& s2) {
        auto s1Len = s1.size();
        auto s2Len = s2.size();
        if (s1Len > s2Len) {
            return false;
        }

        // Check for 's1' being both a prefix and suffix of 's2'
        auto idx = 0;
        for (auto & c : s1) {
            if ((c != s2[idx]) || (c != s2[s2Len - s1Len + idx])) {
                return false;
            }
            ++idx;
        }
        return true;
    }
};
