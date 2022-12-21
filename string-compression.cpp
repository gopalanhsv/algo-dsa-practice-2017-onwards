class Solution {
public:
    int
    compress(vector<char>& chars) {
    
        int arrSz = chars.size();
        if (arrSz <= 1) {
            // Single char string
            return arrSz;
        }
        
        int wrIdx = 0;
        int runCnt = 1;
        char currChar = chars[0];
        // Iterate over the string chars sequentially from L->R
        for (int rdIdx = 1; rdIdx < arrSz; ++rdIdx) {
            if (chars[rdIdx] == chars[rdIdx - 1]) {
                // Current char is identical to previous
                // Update current run length
                ++runCnt;
            } else {
                // Current char is not identical to previous
                // Encode the block in which previous char is present
                if (runCnt > 1) {
                    chars[wrIdx++] = currChar;
                    string runCntStr = to_string(runCnt);
                    for (auto & d : runCntStr) {
                        chars[wrIdx++] = d;
                    }
                } else {
                    chars[wrIdx++] = currChar;
                }
                // Restart new run
                currChar = chars[rdIdx];
                runCnt = 1;
            }
        }
        
        // Encode block with last char
        if (runCnt > 1) {
            chars[wrIdx++] = currChar;
            string runCntStr = to_string(runCnt);
            for (auto & d : runCntStr) {
                chars[wrIdx++] = d;
            }
        } else {
            chars[wrIdx++] = currChar;
        }
        
        chars.resize(wrIdx);
        return wrIdx;
    }
};
