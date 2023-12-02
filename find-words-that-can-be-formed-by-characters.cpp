// d => chars.size()
// n => words.size()
// A => average length of string in words
// M => max length of string in words
// Time complexity : O(d + nA)
// Space complexity : O(d + M)

class Solution {
public:
    int
    countCharacters(vector<string>& words, string chars) {
    
        // Build a hash table/frequency count table for the chars in input dictionary string
        vector<int> dictStrChrFreqCntTbl('a' + 26, 0);
        buildStringCharFreqCntTbl(chars, dictStrChrFreqCntTbl);
        
        int goodWordsTotalLen = 0;
        
        // Iterate over each word sequentially
        for (auto & word : words) {
            
            // Build a hash table/frequency count table for the chars in word string
            vector<int> wordChrFreqCntTbl('a' + 26, 0);
            buildStringCharFreqCntTbl(word, wordChrFreqCntTbl);
            
            // Check if current word can be formed from the input dictionary string by
            // comparing the respective frequency count tables. Each char in word should
            // have a frequency count l.e. has the corresponding char in dictionary
            if (isWordGood(dictStrChrFreqCntTbl, wordChrFreqCntTbl)) {
                // Current word can be formed from the chars in dictionary string
                goodWordsTotalLen += word.size();
            }
        }
        
        return goodWordsTotalLen;
    }
    
private:
    
    inline void
    buildStringCharFreqCntTbl(string& s, vector<int>& chrFreqCntTbl) {
        for (auto & c : s) {
            chrFreqCntTbl[c]++;
        }
    }
    
    bool
    isWordGood(vector<int>& dictChrFreqCntTbl, vector<int>& wordChrFreqCntTbl) {
        for (int i = 0; i != 26; ++i) {
            if (dictChrFreqCntTbl['a' + i] < wordChrFreqCntTbl['a' + i]) {
                return false;
            }
        }
        
        return true;
    }
};
