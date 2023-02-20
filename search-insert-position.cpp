class Solution {
public:
    int
    searchInsert(vector<int>& nums, int target) {
        // Search for target via binary search. If target is not found,
        // l and r cross over with l = r + 1 post search. Covergence
        // position of l with r is lowest index at which element
        // was not present. So new element has to be inserted at final value
        // of l post convergence location
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) {
                // Found target
                return mid;
            } else if (nums[mid] < target) {
                // target to right of mid
                l = mid + 1;
            } else {
                // target to left of mid
                r = mid - 1;
            }
        }
        
        // Search ended with target not found,
        // l & r crossed over with l = r + 1
        return l;
    }
};
