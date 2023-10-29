// n => nums.size()
// Time complexity : O(nk)
// Space complexity : O(1)
class Solution {
public:
    int
    findKOr(vector<int>& nums, int k) {
        
        int kOrNum = 0;
        // Iterate over each bit pos from LSB to MSB
        for (int bitPos = 0; bitPos <= 30; ++bitPos) {
            int numsWithSetBitAtPos = 0;
            int bitMask = 1 << bitPos;
            // Compute the count of numbers with bit set at position 'bitPos'
            for (auto num : nums) {
                if (num & bitMask) {
                    if (++numsWithSetBitAtPos == k) {
                        // Count of nums wit bit set at position 'bitPos' is g.e. 'k'
                        // => bit set at position 'bitPos' in K-or
                        kOrNum |= (bitMask);
                        break;
                    }
                }
            }
        }
        return kOrNum;
    }
};
