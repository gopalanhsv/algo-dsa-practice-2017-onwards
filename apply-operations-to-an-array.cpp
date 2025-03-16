// n => nums.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    vector<int>
    applyOperations(vector<int>& nums) {
        auto n = nums.size();
        vector<int> outV(n, 0);
        auto wrIdx = 0;
        for (auto i = 0; i < n - 1; ++i) {
            if (nums[i] != 0) {
                if (nums[i] == nums[i + 1]) {
                    outV[wrIdx++] = (nums[i] << 1);
                    nums[i + 1] = 0;
                } else {
                    outV[wrIdx++] = nums[i];
                }
            } 
        }

        if (nums[n - 1] != 0) {
            outV[wrIdx] = nums[n - 1];
        }

        return outV;
    }
};
