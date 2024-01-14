// n => word1.size()/word2.size()
// Time complexity : O(n)
// Space complexity : O(26) i.e. O(1)

class Solution {
public:
    bool
    closeStrings(string word1, string word2) {
        if (word1.size() != word2.size()) {
            return false;
        }
        
        // Operation #1 allows any of the string chars to be reordered
        // Operation #2 requires that for a character in word1 to be transformed to
        // another char in word2; both of them should have the identical frequency counts
        
        // From the above 2 requirements, it is evident that if only the frequency counts of
        // unique chars in the two strings are sorted, laid out and compared, the counts should
        // be identical (irrespective of the chars being mathcing/non-matching). Furthermore
        // both the string should be built up of same chars
        
        // Build frequency count table and char presence table for the two strings
        vector<int> word1FreqCntTbl(26, 0);
        vector<int> word2FreqCntTbl(26, 0);
        bitset<26> word1CharTbl;
        bitset<26> word2CharTbl;
        for (auto i = 0; i != word1.size(); ++i) {
            word1FreqCntTbl[int(word1[i] - 'a')]++;
            word1CharTbl[int(word1[i] - 'a')] = 1;
            word2FreqCntTbl[int(word2[i] - 'a')]++;
            word2CharTbl[int(word2[i] - 'a')] = 1;
        }
        
        // Both the words should consist of the same chars
        if (word1CharTbl != word2CharTbl) {
            return false;
        }
        
        // Create an ordered multiset consisting of only the non-zero frequency counts
        // for the various chars present in both word1 and word2. Note that a multiset
        // must be employed instead of a set to capture multiple instances of identical
        // frequency count across different alphabet letters
        multiset<int> word1ChrCntSet, word2ChrCntSet;
        for (auto i = 0; i != 26; ++i) {
            auto & word1ChrFreqCnt = word1FreqCntTbl[i];
            auto & word2ChrFreqCnt = word2FreqCntTbl[i];
            if (0 != word1ChrFreqCnt) {
                word1ChrCntSet.insert(word1ChrFreqCnt);
            }
            if (0 != word2ChrFreqCnt) {
                word2ChrCntSet.insert(word2ChrFreqCnt);
            }
        }
        
        // For allowing re-ordering and transformation, the
        // non-zero char counts must be identical
        
        return (word1ChrCntSet == word2ChrCntSet);
    }
};
