// Time complexity : O(s.size())
// Space complexity : O(k)
class Solution {

public:

    int
    lengthOfLongestSubstringKDistinct(string s, int k) {
        int strSz = s.size();
        // A substring containing at most 'k' distinct char is modelled using
        // a sliding window over the string along with a hash table to track
        // the distinct chars present in the substring/window
        int maxSubstrLen = 0;
        // Hash table tracking the frequency count fo distinct chars in substring
        unordered_map<char, int> winChrFreqTbl;
        // Tracking start of substring
        int winStart = 0;
        // Iterate over the string from L->R seequentially extending the current
        // substring by a char at each step 
        for (int winEnd = 0; winEnd < strSz; ++winEnd) {
            // Current substring extends over the range [winStart, winEnd] 
            auto & currChr = s[winEnd];
            // Add current char to substring
            winChrFreqTbl[currChr]++;
            
            // Shrink the window/substring from left as long as the num
            // of distinct chars exceeds 'k'
            while (winChrFreqTbl.size() > k) {
                auto & winStartChr = s[winStart++];
                if (0 == --winChrFreqTbl[winStartChr]) {
                    winChrFreqTbl.erase(winStartChr);
                }
            }
            
            // Update max substring length seen so far to accomodate
            // current substring length
            maxSubstrLen = max(maxSubstrLen, winEnd - winStart + 1);
        }
        
        return maxSubstrLen;
    }
};
