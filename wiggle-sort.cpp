// Time complexity : O(nums.size())
// Space complexity : O(1)

class Solution {
public:
    void
    wiggleSort(vector<int>& nums) {
        // It is seen that elements at even indices are always <=
        // the ones at odd indices; and elements at odd indices
        // are always >= the ones at even indices.
        
        // Do a linear scan of the array from L->R and swap
        // the elements if they fail the above criteria.
        // At each index location, adopt greedy approach to ensure that
        // the particular element is ordered as per requirements. Adopting
        // a greedy approach locally at each index location leads to the
        // overall array gettting ordered appropriately
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
