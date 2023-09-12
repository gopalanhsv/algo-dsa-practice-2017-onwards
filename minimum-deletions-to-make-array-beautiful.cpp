// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    minDeletion(vector<int>& nums) {
        // 1. Iterate over the array from L->R sequentially
        // 2. Select/retain element  at current index (even indexed). 
        // 3. Now greedily keep deleting adjacent elements to the right of above (advancing
        //    the index at each step) selected element till the closest element n.e to it is
        //    hit or array bounds exceeded. This closest element (if any) would be retained
        //    and would be the odd indexed element
        // 4. Advance to next index. Go to step 2.
        
        int arrSz = nums.size();
        int nDeletions = 0;
        // Element at idx 0 retained/even indexed element
        int prevEvenIdx = 0;
        int nElemsPostDeletion = 1;
        // Iterate over the array from L->R sequentially
        for (auto rdIdx = 1; rdIdx < arrSz; ++rdIdx) {
            if (nums[rdIdx] == nums[prevEvenIdx]) {
                // Delete current element
                ++nDeletions;
            } else {
                // Current element is retained and would be the odd indexed element
                if (rdIdx + 1 < arrSz) {
                    // Advance to next even index as it exists
                    prevEvenIdx = ++rdIdx;
                    nElemsPostDeletion += 2;
                } else {
                    // Array end hit, so not possible to advance to next even index
                    nElemsPostDeletion += 1;
                }
            }
        }
        
        if (nElemsPostDeletion % 2 == 1) {
            // Number of elements in array post deletion should be even
            // => drop last retained element
            ++nDeletions;
        }
        
        return nDeletions;
    }
};
