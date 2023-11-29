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

        auto wStart = -1;

        // Iterate over the array from L->R sequentially
        auto maxWinSize = 0;
        for (auto wEnd = 0; wEnd < arrSz; ++wEnd) {
            if (0 == v[wEnd]) {
                // Current element is a zero
                // Terminate any running window of consecutive ones
                wStart = -1;
            } else {                
                // Current element is a one
                if (-1 == wStart) {
                    // Commence a window of ones at this location if none
                    // continues from previously examined locations
                    wStart = wEnd;
                }
                // Compute window size and update max window size
                auto winSz = wEnd - wStart + 1;
                maxWinSize = max(maxWinSize, winSz);
            }
        }
        
        return maxWinSize;
    }
};
