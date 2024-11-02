// n => sentence.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    bool
    isCircularSentence(string sentence) {
    
        auto & s = sentence;
        auto strSz = s.size();
        if (strSz < 2) {
            return true;
        }
        
        if (s[0] != s[strSz - 1]) {
            // First char does not equal last char => non-circular
            return false;
        }
        
        auto i = 0;
        while (i < strSz) {
            // Skip letters till end of current word end is hit
            i = s.find(' ', i + 1);
            if (i == string::npos) {
                break;
            }
            auto & currWordLastChar = s[i - 1];
            // Skip spaces till new word begins
            while ((i < strSz) && isspace(s[i])) {
                ++i;
            }
            if (i >= strSz) {
                break;
            }
            // Check for equality between first char of next word and last char of current word
            auto & nextWordFirstChar = s[i];
            if (currWordLastChar != nextWordFirstChar) {
                return false;
            }
        }
        
        return true;
    }
};
