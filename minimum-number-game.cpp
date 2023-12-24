// n => nums.size()
// Time complexity : O(nlogn)
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    numberGame(vector<int>& nums) {
        // Alice followed by Bob removing the min element from 'nums' in each
        // round => elements are removed/selected in sorted order in groups of 2
        // i.e. 1st min and 2nd min
        // Since Bob appends the removed element prior to Alice to the output array,
        // the 2nd min comes prior to 1st min in the output for each group of 2
        
        // Sort the array in non-decreasing order s.t. mins get selected in groups of 2
        sort(nums.begin(), nums.end());
        // Iterate over the sorted elems in groups of 2 from L->R
        for (auto i = 0; i < nums.size(); i += 2) {
            // Swap elements to exchange 1st/2nd min in each group of 2
            swap(nums[i], nums[i + 1]);
        }
        return nums;
    }
};
