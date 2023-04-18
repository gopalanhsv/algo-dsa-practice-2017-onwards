// Time complexity : O(word1.size() + word2.size())
// Space complexity : O(1)

class Solution {
public:
    string
    mergeAlternately(string word1, string word2) {
        // Merge technique from merge sort
        int word1Sz = word1.size();
        int word2Sz = word2.size();
        string mergedStr(word1Sz + word2Sz, ' ');
        
        // Read pointer which tracks next index location
        // from which chars in word1/word2 should be read
        int rdIdx = 0;
        // Write pointer which tracks next index location
        // of merged string which should be written to
        int wrIdx = 0;
        // Build merged string using chars alternately from word1 and word2
        // till at least one of the strings is fully read
        int minWordSz = min(word1Sz, word2Sz);
        while (rdIdx < minWordSz) {
            mergedStr[wrIdx++] = word1[rdIdx];
            mergedStr[wrIdx++] = word2[rdIdx];
            // Advance read pointer
            ++rdIdx;
        }
        
        // Merge remaining portion of word1
        while (rdIdx < word1Sz) {
            mergedStr[wrIdx++] = word1[rdIdx++];
        }
        // Merge remaining portion of word2
        while (rdIdx < word2Sz) {
            mergedStr[wrIdx++] = word2[rdIdx++];
        }
        
        return mergedStr;
    }
};
