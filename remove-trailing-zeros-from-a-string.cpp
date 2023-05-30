// Time complexity : O(string length)
// Space complexity : O(1)
class Solution {
public:
    string
    removeTrailingZeros(string num) {
        if (num.empty()) {
            // Base case of empty string
            return num;
        }

        // Scan string chars sequentially from R -> L
        for (int tStrLen = num.size(); tStrLen >= 1; --tStrLen) {
            if (num[tStrLen - 1] != '0') {
                // First non-0 char hit from right. Trailing-0's commence immediately
                // after this character. Drop them by resizing.
                num.resize(tStrLen);
                break;
            }
        }
        
        return num;
    }
};
