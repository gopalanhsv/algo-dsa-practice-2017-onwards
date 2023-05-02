// Time complexity : O(nums.size())
// Space complexity : O(1)
class Solution {
public:
    int
    arraySign(vector<int>& nums) {
        // Any zero in the vector, sign is 0
        // Count the number of -ves;
        int nNegative = 0;
        for (auto & num : nums) {
            if (0 == num) {
                return 0;
            } else if (num < 0) {
                ++nNegative;
            }
        }
        
        // Even number of -ves implies a positive product;
        // Odd number of -ves implies a negative product
        return (0 == (nNegative & 0x1)) ? 1 : -1;
    }
};
