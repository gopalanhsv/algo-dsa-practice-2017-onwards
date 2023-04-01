// Time complexity : O(long nums.size())
// Space complexity : O(1)

class Solution {
public:
    int
    search(vector<int>& nums, int target) {
        
        // Search for 'target' via binary search
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            
            if (nums[mid] == target) {
                return mid;
            }
            
            if (nums[mid] < target) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        
        return -1;
    }
};
