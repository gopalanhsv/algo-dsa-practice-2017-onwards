// n => nums.size();
// Time complexity : O(nlogn)
// Space complexity : O(1)
class Solution {
public:
    int
    sumIndicesWithKSetBits(vector<int>& nums, int k) {
        int arrSz = nums.size();
        if (0 == arrSz) {
            return 0;
        }

        // Iterate over array element sequentially
        int sum = 0;
        for (auto idx = 0; idx != arrSz; ++idx) {
            // Compute the number of set bits in 'idx' by
            // flipping the righmost set bit (at LSB)
            auto nSetBitsInIdx = 0;
            auto x = idx;
            while (x > 0) {
                ++nSetBitsInIdx;
                x = x & (x - 1);
            }
            if (k == nSetBitsInIdx) {
                sum += nums[idx];
            }
        }
        
        return sum;
    }
};
