// Time Complexity : O(array length)
// Space Complexity : O(1)

class Solution {
public:
    long long
    countSubarrays(vector<int>& nums, int minK, int maxK) {
        int arrSz = nums.size();
        
        int closestMaxKIdxToLeft = -1;
        int closestMinKIdxToLeft = -1;
        int fixedBoundRegionStartToLeft = -1;
        int closestMinMaxKIdxToLeft = -1;
        
        long long nSubArrays = 0;
        for (int i = 0; i != arrSz; ++i) {
            auto & elem = nums[i];
            if ((elem < minK) || (elem > maxK)) {
                // In exclusion zone. This array element cannot
                // be in the fixed bound subarray
                closestMaxKIdxToLeft = -1;
                closestMinKIdxToLeft = -1;
                fixedBoundRegionStartToLeft = -1;
                closestMinMaxKIdxToLeft = -1;
                continue;
            }

            if (fixedBoundRegionStartToLeft == -1) {
                fixedBoundRegionStartToLeft = i;
            }
            
            if (elem == minK) {
                closestMinKIdxToLeft = i;
            }
            if (elem == maxK) {
                closestMaxKIdxToLeft = i;
            }
            if ((closestMinKIdxToLeft != -1) && (closestMaxKIdxToLeft != -1)) {
                closestMinMaxKIdxToLeft = min(closestMinKIdxToLeft, closestMaxKIdxToLeft);
            }
            
            if ((fixedBoundRegionStartToLeft != -1) && (closestMinMaxKIdxToLeft != -1)) {
                int nFixedBoundSubArrEndingAtCurrIdx =
                    closestMinMaxKIdxToLeft - fixedBoundRegionStartToLeft + 1;
                
                nSubArrays += nFixedBoundSubArrEndingAtCurrIdx;
            }
        }
        
        return nSubArrays;
    }
};
