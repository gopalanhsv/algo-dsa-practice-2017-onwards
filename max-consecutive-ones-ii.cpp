// n => v.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    findMaxConsecutiveOnes(vector<int>& v) {
        auto arrSz = v.size();

        if (0 == arrSz) {
            // Base case of empty input vector
            return 0;
        }

        if (1 == arrSz) {
            // Base case of single element vector
            return 1;
        }

        // Use a sliding window to keep track of consecutives ones seen
        // with a single zero flip. This window of ones is delimited by 
        // range [winStart, winEnd]
        bool zeroFlipDoneInWindow = false;
        auto maxWinSz = 0;
        auto winStart = 0;
        auto locationOfPrevZeroFlip = 0;
        auto winEnd = 0;
        // Iterate over the array from L->R adding a new binary char to right of window
        for (; winEnd != arrSz; ++winEnd) {
            // New incoming element is a 0
            if (v[winEnd] == 0) {
                // Need to flip at this location and adjust window start if required
                
                if (zeroFlipDoneInWindow) {
                    // Single zero flip already done earlier in window
                    // Terminate current running window of consecutives ones here.
                    auto winSize = winEnd - winStart;
                    // Update max window size with consective ones
                    maxWinSz = max(winSize, maxWinSz);
                    // Shift window start to immediate right of previous zero flip
                    // and flip current zero
                    winStart = locationOfPrevZeroFlip + 1;
                }

                // Flip zero at current location
                zeroFlipDoneInWindow = true;
                locationOfPrevZeroFlip = winEnd;
            }
            
            // Nothing needs to done if 1s are encountered
        }
        
        // Update max number of consecutive ones see so far
        maxWinSz = max(winEnd - winStart, maxWinSz);
        
        return maxWinSz;
    }
};
