class Solution {
public:
    int
    removeDuplicates(vector<int>& nums) {
        int arrSz = nums.size();

        // Single element/null vector
        if (1 >= arrSz) {
            return arrSz;
        }

        int wrIdx = 1;
        // Since vector is sorted, duplicates are adjacent
        // Iterate over all elements of array sequentially
        for (int rdIdx = 1; rdIdx != arrSz; ++rdIdx) {
            if (nums[rdIdx] != nums[wrIdx - 1]) {
                // Unique element seen since last write
                // Move unique element to write pointer
                // and update the pointer
                nums[wrIdx++] = nums[rdIdx]; 
            }
            
        }

        return wrIdx;      
    }
};
