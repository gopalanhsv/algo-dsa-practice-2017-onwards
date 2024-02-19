// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    returnToBoundaryCount(vector<int>& nums) {
        long long netOffset = 0;
        int count = 0;
        // Iterate over each step in sequence
        for (auto & step : nums) {
            // Compute the net offset from boundary
            netOffset += step;
            count += (0 == netOffset);
        }
        return count;
    }
};
