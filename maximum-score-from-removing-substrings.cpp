// n => s.size()
// Time complexity : O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    maximumGain(string s, int x, int y) {
        if (s.size() < 2) {
            return 0;
        }

        // Adopt the greedy approach of removing all instances of substring which have a
        // higher score, prior to removing all instances of substring which have a
        // lower score to maximize gain
        int gain = 0;
        if (x < y) {
            // Removal of all instances of "ba" from 's' prior to removal
            // of all instances of "ab" leads to a higher gain
            gain += removeSubstring(s, "ba", y);
            gain += removeSubstring(s, "ab", x);
        } else {
            // Removal of all instances of "ab" from 's' prior to removal
            // of all instances of "ba" leads to a higher gain
            gain += removeSubstring(s, "ab", x);
            gain += removeSubstring(s, "ba", y);
        }
        
        return gain;
    }
    
private:

    int
    removeSubstring(string& s, string subStr, int score) {
        auto strSz = s.size();
        auto wrIdx = 0;
        
        int totalScore = 0;
        auto firstChar = subStr[0];
        auto secondChar = subStr[1];
        for (auto rdIdx = 0; rdIdx < strSz; ++rdIdx) {
            auto & currChar = s[rdIdx];
            if (wrIdx > 0) {
                auto & prevChar = s[wrIdx - 1];
                if ((currChar == secondChar) && (prevChar == firstChar)) {
                    --wrIdx;
                    totalScore += score;
                } else {
                    s[wrIdx++] = currChar;
                }
            } else {
                s[wrIdx++] = currChar;
            }
        }
        
        s.resize(wrIdx);
        return totalScore;
    }
};
