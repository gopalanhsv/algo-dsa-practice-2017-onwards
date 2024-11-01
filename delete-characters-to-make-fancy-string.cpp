// n => s.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    string
    makeFancyString(string s) {
        // Iterate over the string chars sequentially. Track groups of consecutive chars
        // employing a counter; dropping consecutive equal chars whenever the counter exceeds 2
        // Use a write pointer to write only required chars and skip unnecessary ones
        int wrPtr = 1;
        int nConsecutiveEqualChars = 1;
        for (int i = 1; i != s.size(); ++i) {
            if (s[i] == s[i - 1]) {
                // Consective same chars
                ++nConsecutiveEqualChars;
                if (nConsecutiveEqualChars < 3) {
                    // Count of consecutive same chars less than 3;
                    // so copy the chars
                    s[wrPtr++] = s[i];
                }
            } else {
                // Consective chars non-equal. Reset counter and copy chars
                nConsecutiveEqualChars = 1;
                s[wrPtr++] = s[i];
            }
        }
        
        // Resize the string to account for dropped chars
        s.resize(wrPtr);
        return s;
    }
};
