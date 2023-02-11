class Solution {
public:
    void
    wiggleSort(vector<int>& nums) {
        // It is seen that elements at even indices are always <=
        // the ones at odd indices; and elements at odd indices
        // are always >= the ones at even indices.
        
        // Achieved by a linear scan of the array from L->R and
        // swapping the elements if they fail the above criteria.
        // At each index adopt greedy approach to ensure that
        // the particular element is ordered as the requirements
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (i % 2 == 0) {
                // Even index. Elements at even index should always
                // be l.t. element at succeeding odd index
                // Swap elements failing this condition
                if (nums[i] > nums[i + 1]) {
                    swap(nums[i], nums[i + 1]);
                }
            } else {
                // Odd index. Elements at odd index should always
                // be g.t. element at succeeding even index
                // Swap elements failing this condition
                if (nums[i] < nums[i + 1]) {
                    swap(nums[i], nums[i + 1]);
                }
            }
        }
    }
};
