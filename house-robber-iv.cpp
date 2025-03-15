// n => nums.size(), M => max element value in 'nums'
// Time Complexity : O(nlogM)
// Space Complexity : O(1)

class Solution {
public:
    int
    minCapability(vector<int>& nums, int k) {
        // Robber robs a minimum of 'k' non-adjacent houses

        // Determine the possible range of capability values
        int minVal = nums[0];
        int maxVal = nums[0];
        for (auto & num : nums) {
            minVal = min(num, minVal);
            maxVal = max(num, maxVal);
        }

        int l = minVal;
        int r = maxVal;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (possibleToRobKHousesWithGivenCapability(nums, k, mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }

        return l;
    }

private:

    bool
    possibleToRobKHousesWithGivenCapability(
        vector<int>& nums, int k, int capability) {
        
        int robbedHouseCnt = 0;
        for (auto houseIdx = 0; houseIdx < nums.size(); ++houseIdx) {
            if (capability >= nums[houseIdx]) {
                ++robbedHouseCnt;
                ++houseIdx;
            }
        }

        return robbedHouseCnt >= k;
    }
};
