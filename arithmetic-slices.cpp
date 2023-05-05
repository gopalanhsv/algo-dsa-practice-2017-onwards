// Time complexity : O(nums.size())
// Space complexity : O(1)

class Solution {
public:
    int
    numberOfArithmeticSlices(vector<int>& nums) {
        int arrSz = nums.size();
        if (arrSz < 3) {
            // Base case of no arithmetic slices due to small array size
            return 0;
        }
        
        // Subarray delimited by closed range [start, end] contains elements s.t
        // difference between any 2 consecutive elements is identical
        // i.e. the subarrays of nums[start, end] form arithmetic slices
        int nSlices = 0;
        int start = 0;
        // Flag to determine commencement/continuation of a subarray with
        // same diff between the elements 
        bool allSubArrElemsWithSameDiff = false;
        // Attempt to extend the size of current subarray/create a new subarray
        // by adding a new element from the original array sequentially
        for (int end = 2; end != arrSz; ++end) {
            auto & currElem = nums[end];
            if (currElem - nums[end - 1] == nums[end - 1] - nums[end - 2]) {
                // 3 consecutive elements ending at current element
                // with index 'end' have the same diff
                if (!allSubArrElemsWithSameDiff) {
                    // New subarray with same diff between consecutive elements
                    // and 3 elements commences (a new arithmetic slice)
                    allSubArrElemsWithSameDiff = true;
                    // Update start of new subarray and increment slice count
                    start = end - 2;
                    nSlices++;
                } else {
                    // Extension/Continuation of subarray with same diff between
                    // consecutive elements by current element
                    // Update subarray size
                    int subArrSz = end - start + 1;
                    // Count of arithmetic slices which end at/include current element
                    int nNewSlicesAdded = subArrSz - 2;
                    // Update number of slice
                    nSlices += nNewSlicesAdded;
                }
            } else {
                // 3 consecutive elements ending at current element
                // with index 'end' dont have same diff - mark flag as such
                allSubArrElemsWithSameDiff = false;
            }
        }
        
        return nSlices;
    }
};
