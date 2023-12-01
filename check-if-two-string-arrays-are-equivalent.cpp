// n1 => total chars in word1, n2 => total chars in word2
// Time complexity : O(min(n1, n2))
// Space complexity : O(1)

class Solution {
public:
    bool
    arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        // Array sizes
        int word1ArrSz = word1.size();
        int word2ArrSz = word2.size();
        // Pointers tracking the current word in the respective arrays
        int word1ArrIdx = 0;
        int word2ArrIdx = 0;
        // Pointers tracking the current char in current word
        // in the respective arrays
        int word1ChrIdx = 0;
        int word2ChrIdx = 0;
        
        while ((word1ArrIdx < word1ArrSz) && (word2ArrIdx < word2ArrSz)) {
            
            // Compare current chars and advance to next char in the respective arrays
            if (word1[word1ArrIdx][word1ChrIdx++] != word2[word2ArrIdx][word2ChrIdx++]) {
                // Chars do not match => strings are not equivalent
                return false;
            }
            
            // Advance to next word in word1
            if (word1ChrIdx == word1[word1ArrIdx].size()) {
                word1ChrIdx = 0;
                ++word1ArrIdx;
            }
            // Advance to next word in word2
            if (word2ChrIdx == word2[word2ArrIdx].size()) {
                word2ChrIdx = 0;
                ++word2ArrIdx;
            }
        }
    
        if ((word1ArrIdx < word1ArrSz) || (word2ArrIdx < word2ArrSz)) {
            // One of the 2 word arrays in not fully explored
            return false;
        }
    
        // Equivalent strings
        return true;
    }
};
