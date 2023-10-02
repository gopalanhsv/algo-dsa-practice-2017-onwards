// Time complexity : O(nums.size())
// Space complexity : O(k)
class Solution {
public:
    int
    minOperations(vector<int>& nums, int k) {
        // Hash table tracking collected elements
        vector<bool> collectedElemsV(k + 1, false);
        int nCollectedElems = 0;
        // Iterate over the array sequentially from back to front
        for (auto i = nums.size() - 1; i >= 0; --i) {
            auto & currElem = nums[i];
            // Remove the current element from array end/back
            // Collect elem if in range [1, k] and not collected earlier
            if ((currElem >= 1) && (currElem <= k) && !collectedElemsV[currElem]) {
                collectedElemsV[currElem] = true;
                if (++nCollectedElems == k) {
                    // All elements in range [1, k] are collected. Number of operations
                    // would be the number of removed elements i.e. [i, nums.size() - 1)]
                    return nums.size() - i;
                }
            }
        }
        
        // Error condition of all elements in range [1, k] not getting removed (should not be hit)
        return -1;
    }
};
