// s.size() => n
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    string
    finalString(string s) {
        // Tracks the output string
        list<char> outStrChrList;
        bool reverseSeenSubStr = false;
        // Iterate over the string chars from L->R sequentially
        for (auto & c : s) {
            if ('i' == c) {
                // Reverse the string written so far
                reverseSeenSubStr = !reverseSeenSubStr;
            } else {
                if (reverseSeenSubStr) {
                    // String is being written in reversed mode
                    // Append new char to beginning of output
                    outStrChrList.push_front(c);
                } else {
                    // String is being written in normal mode
                    // Append new char to end of output
                    outStrChrList.push_back(c);
                }
            }
        }
        
        // Final output
        if (reverseSeenSubStr) {
            // Written string should be reversed and displayed
            return string(outStrChrList.rbegin(), outStrChrList.rend());
        }
        
        // Written string should be displayed as is
        return string(outStrChrList.begin(), outStrChrList.end());
    }
};
