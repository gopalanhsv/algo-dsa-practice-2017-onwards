// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(n)
class Solution {
public:
    int
    missingInteger(vector<int>& nums) {
        // Iterate over the array sequentially from L->R to determine
        // the longest sequential prefix starting at index '0' and its sum
        auto longestSeqPfxSum = nums[0];
        for (auto i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1] + 1) {
                break;
            }
            longestSeqPfxSum += nums[i];
        }
        
        // Hash table of array elements
        unordered_set<int> numsTbl(nums.begin(), nums.end());
        // Determine the smallest element g.e the longest sequential prefix
        // sum which is missing from the array
        auto smallestMissing = longestSeqPfxSum;
        while (numsTbl.find(smallestMissing) != numsTbl.end()) {
            ++smallestMissing;
        }
        
        return smallestMissing;
    }
};
