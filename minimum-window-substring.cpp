// m => s.size()
// n => t.size()
// Time complexity : O(m + n)
// Space complexity : O(m + n)

class Solution {
public:
    string
    minWindow(string s, string t) {
        if (s.empty() || t.empty()) {
            // Base case of either of the text/pattern strings being empty
            return "";
        }

        // Build character frequency count table for pattern string 't'
        unordered_map<char, int> tChrFreqCntTbl;
        for (auto & c : t) {
            tChrFreqCntTbl[c]++;
        }

        // Use a variable sized sliding window to determine the minimum
        // window substring of the search text 's' which has all chars
        // (including duplicates) of pattern string 't'
        int minSubStrStart = -1;
        int minSubStrLen = 0;

        // Scan the text string from left to right till a char is found
        // which occurs in the search text. The sliding window will
        // commence from there
        int strSz = s.size();
        int wStart = 0;
        while ((wStart < strSz) &&
               (0 == tChrFreqCntTbl.count(s[wStart]))) {
            ++wStart;
        }

        unordered_map<char, int> winStrChrFreqCntTbl;
        for (auto wEnd = wStart; wEnd < strSz; ++wEnd) {
            // Add current char to window
            auto & currChr = s[wEnd];
            winStrChrFreqCntTbl[currChr]++;
            // Shrink window from left as long as the window text
            // contains all pattern characters
            while (textContainsPattern(winStrChrFreqCntTbl, tChrFreqCntTbl)) {
                // Current window text contains pattern chars
                auto wLen = wEnd - wStart + 1;
                if ((0 == minSubStrLen) || (wLen < minSubStrLen)) {
                    // Current window size is minimum seen so far with required pattern
                    minSubStrStart = wStart;
                    minSubStrLen = wLen;
                }

                // Shrink window from left
                auto & wStartChr = s[wStart++];
                winStrChrFreqCntTbl[wStartChr]--;
            }
        }

        return (0 == minSubStrLen) ? "" : s.substr(minSubStrStart, minSubStrLen);
    }
    
private:
    
    bool
    textContainsPattern(unordered_map<char, int>& textChrFreqCntTbl,
                        unordered_map<char, int>& patternChrFreqCntTbl) {

        if (textChrFreqCntTbl.size() < patternChrFreqCntTbl.size()) {
            return false;
        }

        // Every char in the pattern must be present in the text with at least the
        // same frequency count; for the text to have all the pattern chars
        for (auto & patternChrFreqCntEntry : patternChrFreqCntTbl) {
            auto & pChr = patternChrFreqCntEntry.first;
            auto & pChrFreqCnt = patternChrFreqCntEntry.second;
            auto iter = textChrFreqCntTbl.find(pChr);
            if ((iter == textChrFreqCntTbl.end()) ||
                (iter->second < pChrFreqCnt)) {
                // Pattern char not found in text or present with
                // present with lesser chars
                return false;
            }
        }
        
        return true;
    }
};
