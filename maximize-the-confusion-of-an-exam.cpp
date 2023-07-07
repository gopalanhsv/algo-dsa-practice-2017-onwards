// Time complexity : O(answerKey.size()) / O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    maxConsecutiveAnswers(string answerKey, int k) {
        // Since at most 'k' 'T' can be flipped to 'F' or vice versa ('F' to 'T'),
        // the problem reduces to finding the maximum length subarray of contiguous
        // 'T' interspersed with at most 'k' 'F''s (wich can be flipped to 'T');
        // and the maximum length subarray of contiguous 'F' interspersed with at
        // most 'k' 'T''s (wich can be flipped to 'F'); and choosing the maximum
        // of these two computed lengths
        
        // The above is easily determined using sliding window technique
        // (requires two sliding windows :
        // 1st tracking the maximum subarray of contiguous 'T''s with at most 'k' 'F's &
        // 2nd tracking the maximum subarray of contiguous 'F''s with at most 'k' 'T's
        
        // Window # 1 of contiguous 'T''s extends over the range [sWinStartT, sWinEnd]
        // Window # 2 of contiguous 'F''s extends over the range [sWinStartF, sWinEnd]
        
        int strSz = answerKey.size();
        int maxSubArrLen = 0;
        // Set the start of the 2 windows of 'True' and 'False' respectively
        int sTrueWinStart = 0;
        int sFalseWinStart = 0;
        // Tracks count of 'True' in the window # 2 of 'False'
        int nTrue = 0;
        // Tracks count of 'False' in the window # 1 of 'True'
        int nFalse = 0;
        // Extend the window to the right by one element in each iteration
        for (int sWinEnd = 0; sWinEnd < strSz; ++sWinEnd) {

            // Increment count of 'True'/'False' for new char added to right of window
            if ('T' == answerKey[sWinEnd]) {
                ++nTrue;
            } else {
                ++nFalse;
            }
            
            // Number of 'False' exceeds 'k', Shrink the window #1 of 'True's from the
            // left till window contains at most 'k' 'False'. These 'k' 'False' can be
            // replaced by 'True' and the entire window #1 consists only of 'True'
            while (nFalse > k) {
                if (answerKey[sTrueWinStart++] == 'F') {
                    --nFalse;
                }
            }
            // Compute the len of window of 'True's ending at 'sWinEnd' 
            auto currTrueWinLen = sWinEnd - sTrueWinStart + 1;
            // Update the max window length seen so far
            maxSubArrLen = max(maxSubArrLen, currTrueWinLen);
            
            // Number of 'True' exceeds 'k', Shrink the window #2 of 'False' from the
            // left till window contains at most 'k' 'True'. These 'k' 'True' can be
            // replaced by 'False' and the entire window #2 consists only of 'False'
            while (nTrue > k) {
                if (answerKey[sFalseWinStart++] == 'T') {
                    --nTrue;
                }
            }
            // Compute the len of window of 'False's ending at 'sWinEnd' 
            auto currFalseWinLen = sWinEnd - sFalseWinStart + 1;
            // Update the max window length seen so far
            maxSubArrLen = max(maxSubArrLen, currFalseWinLen);
        }
        
        return maxSubArrLen;
    }
};
