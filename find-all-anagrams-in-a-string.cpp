class Solution {
public:
    vector<int>
    findAnagrams(string s, string p) {
        vector<int> outV;
        // Base case of either of string being empty or search
        // block being bigger than text block
        if (s.empty() || p.empty() || p.size() > s.size()) {
            return outV;
        }
    
        // Init the frequency count table for fixed string 'p'
        // whose anagram is searched for in text 's'
        for (auto c : p) {
            _patternStrFreqCntTbl[c]++;
        }
        
        // Have a sliding window of size p.size() [pattern size]
        // which will be shifted from left of text to the end of text
        // one character at a time. Maintain a continuously updating 
        // frequency count table of the text block delimited by the 
        // sliding window. The frequency count table of pattern string should
        // be identical the frequency count table of sliding window text string;
        // for sliding window chars to be anagram of fixed size string
        
        // Doing this 'a' + 26 for perf improvement else have to - 'a' in all
        // indexing of text block char counter table
        vector<int> sWindowCharFreqV('a' + 26, 0); 
        typedef string::size_type strSzT;
        strSzT winStart = 0;
        strSzT winSize = p.size();
        // Sliding window of fixed size p.size() delimited by [winStart, winEnd]
        for (strSzT winEnd = 0; winEnd < s.size(); ++winEnd) {
            // Add new char to window and update the freq count for
            // incoming char
            sWindowCharFreqV[s[winEnd]]++;
            
            if (winEnd - winStart + 1 == winSize) {
                // Window size of text block is search pattern size
                if (isTextBlockAnagramOfSearchPattern(sWindowCharFreqV)) {
                    // Window Text block is an anagram of search pattern
                    // Store text block init pos
                    outV.emplace_back(winStart);
                }
                
                // Advance start of window & update freq cnt of outgoing char
                --sWindowCharFreqV[s[winStart++]];
                //++winStart;
            }
        }
        
        return outV;
    }
    
private:
    
    bool
    isTextBlockAnagramOfSearchPattern(vector<int>& textBlockChrFreqTbl) {
        // Iterate over search pattern freq count hash table.
        // Search pattern freq count for all chars should match
        // the text block char freq count for same chars
        for (auto & cfce : _patternStrFreqCntTbl) {
            // cfce => char frequency count entry
            if (cfce.second != textBlockChrFreqTbl[cfce.first]) {
                return false;
            }
        }
        
        return true;
    }
    
    // Data members
    // Character frequency count table of search pattern string
    // (data member to avoid passing in func calls)
    unordered_map<char, int> _patternStrFreqCntTbl;
};
