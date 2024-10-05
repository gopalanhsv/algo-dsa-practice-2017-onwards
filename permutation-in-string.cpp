// m => s1.size(), n => s2.size()
// Time complexity : O(m + n)
// Space complexity : O(m)

class Solution {
public:
    bool
    checkInclusion(string s1, string s2) {
        if (s1.empty() || s2.empty() || s1.size() > s2.size()) {
            return false;
        }

        // Problem reduces to checking whether an anagram/permutation of
        // string pattern s1 exists in the search text s2
        string & txtStr = s2;
        string & patternStr = s1;

        // Checking for existence of anagram of pattern in text simply
        // involves searching for pattern in text using a sliding window
        // of chars (of length pattern size) delimiting a text block
        // within the search text. The pattern is compared with text block
        // using frequency count tables of pattern & window text
        
        // Construct frequency table of search pattern chars
        for (auto c : patternStr) {
            ++_patternCharFreqTbl[c];
        }
        
        // Frequency table of text block string delimited by sliding window
        // 26 entries as our problem operates with only English lower case letters
        // Doing the 'a' + 26 for perf improvement to avoid computing x - 'a' for
        // all subsequent indexing of below table
        vector<int> sWinBlockChrFreqTbl('a' + 26, 0);
        
        auto sWinStart = 0;
        auto sWinSize = patternStr.size(); // Sliding window len
        
        // Sliding of text block within text string delimited by [sWinStart, sWindEnd]
        // Iterate over the characters over the text string sequentially
        // adding them to the sliding window
        for (auto sWinEnd = 0; sWinEnd < txtStr.size(); ++sWinEnd) {
            
            // Update frequency count of new incoming char to the window
            ++sWinBlockChrFreqTbl[txtStr[sWinEnd]];
            
            if (sWinEnd - sWinStart + 1 == sWinSize) {
                
                // Window size is same as pattern length
                if (areAnagrams(sWinBlockChrFreqTbl)) {
                    // Text block within sliding window is an anagram
                    // of the search pattern
                    return true;
                }
                
                // Advance the start of the window and update the
                // frequency count of outgoing character
                --sWinBlockChrFreqTbl[txtStr[sWinStart++]];
            }
        }
        
        // Search pattern string permutation/anagram not found
        return false;
    }
    
    
private:
    
    bool
    areAnagrams(vector<int>& txtBlockCharFreqTbl) {
        // Check if the tables of pattern string character frequency
        // and sliding window text block character frequency are identical
        for (auto & pcfte : _patternCharFreqTbl) {
            // pcfte => pattern character frequency table entry
            if (txtBlockCharFreqTbl[pcfte.first] != pcfte.second) {
                return false;
            }
        }
        return true;
    }
    
    // Data members
    
    // Frequency table of search text chars
    unordered_map<char, int> _patternCharFreqTbl;    
};
