// Time Complexity : O(nrow * ncol)
// Space Complexity : O(1)

class Solution {
public:
    bool
    validWordSquare(vector<string>& words) {
        
        int nw = words.size();
        // Iterate over each word sequentially
        for (int r = 0; r < nw; ++r) {
            // Current word (horizontal) @ current row 'r'
            auto & rowWord = words[r];
            int wordSz = rowWord.size();
            if (wordSz > nw) {
                // Current word size exceeds the max possible
                // col size(number of words)
                return false;
            }
            
            // Compare the current horizontal word in row 'r' char by
            // char with the appropriate vertical word in col 'r' 
            int colIdx = r;
            // Iterate over chars of current row word from L->R
            for (int chrIdx = 0; chrIdx < wordSz; ++chrIdx) {
                
                if (words[chrIdx].size() <= colIdx) {
                    // Corresponding column word for col 'r' has a size mismatch
                    return false;
                }
                
                if (rowWord[chrIdx] != words[chrIdx][colIdx]) {
                    // Mismatch between correponding chars of row word and col word
                    return false;
                }
            }
        }
        
        return true;
    }
};
