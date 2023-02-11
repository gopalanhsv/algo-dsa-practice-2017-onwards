class Solution {
public:
    void
    wiggleSort(vector<int>& nums) {
        // It is seen that elements at even indices are always <=
        // the ones at odd indices; and elements at odd indices
        // are always >= the ones at even indices.
        
        // So the above can be done by a linear scan of the array
        // from left to right and swapping the elements if they
        // fail the above criteria. At each index we take the
        // greedy decision of ensure that the element at that
        // index is ordered as the requirements;
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (i % 2 == 0) {
                // i is even index. Elements at even index should always
                // be lesser than the element at odd index
                // Swap elements failing this condition
                if (nums[i] > nums[i + 1]) {
                    swap(nums[i], nums[i + 1]);
                }
            } else {
                // i is odd index. Elements at odd index should always
                // be greater than the element at even index
                // Swap elements failing this condition
                if (nums[i] < nums[i + 1]) {
                    swap(nums[i], nums[i + 1]);
                }
            }
        }
    }
};
