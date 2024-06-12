// n => nums.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    void
    sortColors(vector<int>& nums) {
        //sortColorsTwoPass(nums);
        sortColorsOnePass(nums);
    }
    
private:
    
    void
    sortColorsTwoPass(vector<int> & nums) {
        // First pass move all 0's to array front
        int zeroWrIdx = 0;
        for (auto & e : nums) {
            if (e == 0) {
                swap(e, nums[zeroWrIdx++]);   
            }
        }
        // Second pass move all 2's to array rear
        // Note the array traversal is from R->L
        int twoWrIdx = nums.size() - 1;
        for (int rdIdx = nums.size() - 1; rdIdx >= zeroWrIdx; --rdIdx) {
            auto & e = nums[rdIdx];
            if (e == 2) {
                swap(e, nums[twoWrIdx--]);   
            }
        }
        
        // 1's will get automatically placed
    }
    
    void
    sortColorsOnePass(vector<int> & nums) {
        int zeroWrIdx = 0;
        int twoWrIdx = nums.size() - 1;
        // Iterate over the array elements from L->R sequentially
        for (int i = 0; i <= twoWrIdx;) {
            if (nums[i] == 0) {
                // '0' gets swapped with element at current 0 write location (array front)
                swap(nums[i++], nums[zeroWrIdx++]);
            } else if (nums[i] == 2) {
                // '2' gets swapped with element at current 2 write location (array end)
                swap(nums[i], nums[twoWrIdx--]);
            } else {
                // Advance to next element if '1'
                ++i;
            }
        }
    }
};
