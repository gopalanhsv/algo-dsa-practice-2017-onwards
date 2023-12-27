// n => s.size()
// Time complexity : O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    lengthOfLongestSubstringTwoDistinct(string s) {
        // Use a sliding window to delimit the substring with at most 2 distinct chars
        // Hash table tracking frequency count of chars in the substring
        // delimited by the sliding window
        vector<int> winCharFreqTbl(256, 0);
        int nDistinctWindowChars = 0;
        
        auto winStart = 0;
        auto maxWinSz = 0;
        // Iterate over the string chars from L->R sequentially adding one char at a time
        // to the right of the window. Window range is [winStart, winEnd]
        for (auto winEnd = 0; winEnd != s.size(); ++winEnd) {
            // Add new character to window
            auto & c = s[winEnd];
            // Update character frequency count table for current char added to window
            if (winCharFreqTbl[c]++ == 0) {
                // New char added is a new distinct char
                ++nDistinctWindowChars;
                // Shrink the window from the left one char at a time till the substring
                // delimited by the window [winStart, winEnd] contains at most 2 distinct chars
                while (nDistinctWindowChars > 2) {
                    auto & removedChar = s[winStart++];
                    if (--winCharFreqTbl[removedChar] == 0) {
                        --nDistinctWindowChars;
                    } 
                }
            }
            
            // Update character frequency count table for current char added
            //winCharFreqTbl[c]++;
            
            // Update max window size to account for current window
            maxWinSz = max(maxWinSz, winEnd - winStart + 1);
        }
        
        return maxWinSz;
    }
};
