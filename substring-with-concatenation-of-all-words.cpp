class Solution {
public:
    vector<int>
    findSubstring(string s, vector<string>& words) {
        // Concatenating all words in the array in any order leads
        // to a string which should be a substring of 's'
        // Build the frequency count table of each letter char in
        // concatened word string; and a frequency count table of
        // each word forming the concatenated string
        int wordLen = words[0].size();
        int concatStrLen = wordLen * words.size();
        unordered_map<string, int> concatWordFreqCntTbl;
        vector<int> concatWordCharFreqCntTbl(26, 0);
        initialize(words, concatWordFreqCntTbl, concatWordCharFreqCntTbl);
        
        // Output array with the starting indices of substring(s) 
        // location within the string 's', which is a concatenation
        // of all words
        vector<int> matchLocationV;
        
        // Use a sliding window of size equal to the string length of 
        // concatenated words, to select all possible substrings within
        // the string 's' which may have the concatenated words string
        // For each of the selected substrings delineated by the sliding
        // window, check whether it a concatenated string of all words
        // (this will require all chars in sliding window substring to
        // have same number of occiurences as the corresponding chars in the
        // concatenated words string and vice versa; and all words in
        // the concatenated word string should occur in the sliding window
        // substring with the same occurence count)
        
        // Frequency count table tracking occurence count of
        // each char within the sliding window substring
        vector<int> winCharFreqCntTbl(26, 0);
        int strSz = s.size();
        int winStart = 0;
        // Keep sliding the right side of the window by one at each step
        // to evaluate each possible substring candidate which can be a
        // concatenation
        for (int winEnd = 0; winEnd != strSz; ++winEnd) {
            // Adding a new char to the window from right side
            auto & currChar = s[winEnd];
            winCharFreqCntTbl[currChar - 'a']++;
            
            int winLen = winEnd - winStart + 1;
            if (winLen == concatStrLen) {
                // Sliding window range encloses a substring of same length
                // as the concatenated word string
                
                // Check if sliding window range encloses a variant of the
                // concatenated word string
                // 1. All chars in concatenated word string should be present
                // in sliding window
                // 2. All words in concatenated word string should be present
                // in sliding window
                if (winCharFreqCntTbl == concatWordCharFreqCntTbl) {
                    if (subStrIsAConcatenationOfWords(
                        s, winStart, winEnd, wordLen, concatWordFreqCntTbl)) {
                        // Sliding window substring is a concatenated word string
                        matchLocationV.emplace_back(winStart);
                    }
                }
                
                // Advance the left/start of the window by one step to right
                // in prep for next iteration; and update the internal state
                auto & winStartChar = s[winStart++];
                winCharFreqCntTbl[winStartChar - 'a']--;
            }
        }
        
        return matchLocationV;
    }
    
private:
    
    bool
    subStrIsAConcatenationOfWords(string& s, int start, int end,
                                  int wordLen, unordered_map<string, int>& wordFreqCntTbl) {
        // Split the substring into consecutive words of length 'wordLen'
        // Build a frequency count table which tracks the count of each consecutive
        // word of len 'wordLen' (as per input constraints) present in the substring
        // marked by the sliding window s[start, end]
        int sLen = end - start + 1;
        unordered_map<string, int> winStrWordFreqCntTbl;
        for (int i = start; i <= end; i += wordLen) {
            auto word = s.substr(i , wordLen);
            if (wordFreqCntTbl.find(word) == wordFreqCntTbl.end()) {
                // Current word in window is not present in the
                // set of concatenated words. So sliding window
                // cannot have the concatenated words
                return false;
            }
            winStrWordFreqCntTbl[word]++;
        }
        
        // Each word in the concatenated string should be present in window with
        // identical occurence count
        for (auto & wordFreqCntP : wordFreqCntTbl) {
            auto & word = wordFreqCntP.first;
            auto & freqCnt = wordFreqCntP.second;
            if (winStrWordFreqCntTbl[word] != freqCnt) {
                return false;
            }
        }
        
        return true;
    }
    
    void
    initialize(vector<string>& words,
               unordered_map<string, int>& wordFreqCntTbl,
               vector<int>& charFreqCntTbl) {
        // Iterate over each word in array of words
        // Build a word frequency count table for the array words; and
        // character frequency count table of every character belonging
        // to words in the array
        for (auto & word : words) {
            wordFreqCntTbl[word]++;
            for (auto & c : word) {
                charFreqCntTbl[c - 'a']++;
            }
        }
    }
};
