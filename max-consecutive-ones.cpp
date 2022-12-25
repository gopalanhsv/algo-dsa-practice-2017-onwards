class Solution {
public:
    int
    findMaxConsecutiveOnes(vector<int>& v) {
        // Empty input vector
        if (v.empty()) {
            return 0;
        }
        
        typedef vector<int>::size_type vecSzT;
        // Skip leading zeroes till the first 1 is found. Commence
        // a sliding expanding window from this point
        vecSzT winStart = 0;
        while (winStart < v.size() && v[winStart] != 1) {
            ++winStart;
        }

        // Examine all elements of vector sequentially
        vecSzT maxWinSize = 0;
        for (vecSzT winEnd = winStart; winEnd < v.size(); ++winEnd) {
            
            // Current element is a zero,
            if (v[winEnd] == 0) {
                
                // Previous window of ones gets terminated
                // Now adjust start of window by skipping zeroes till a one
                // is reached (start of next window) or vector terminates
                winStart = winEnd;
                while (winStart < v.size() && v[winStart] != 1) {
                    ++winStart;
                }
                winEnd = winStart;
                
            } else {
                
                // Current element is a one, expand window
                // Compute its size and update max window size. 
                vecSzT winSize = winEnd - winStart + 1;
                maxWinSize = max(maxWinSize, winSize);
            }
            
        }
        
        return maxWinSize;
        
    }
};
