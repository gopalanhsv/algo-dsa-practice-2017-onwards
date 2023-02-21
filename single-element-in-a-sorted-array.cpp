class Solution {
public:
    int
    singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        
        if (n == 1) {
            // Single unique element
            return nums[0];
        }
        
        // Unique element at beginning or end
        if (nums[0] != nums[1]) {
            return nums[0];
        }
        if (nums[n - 2] != nums[n - 1]) {
            return nums[n - 1];
        }
        
        // Array is sorted => binary search technique
        // If the single non-duplicate element is located at index 'i',
        // and all other elements are duplicates implies the following:-
        // 1. All elements prior to index 'i' would be s.t.
        // element will be at even index and its duplicate at odd index
        // 2. All elements post index 'i' would be s.t.
        // element will be at odd index and its duplicate at even index
        
        int lo = 0, hi = n - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            
            if (nums[mid] != nums[mid - 1] &&
                nums[mid] != nums[mid + 1]) {
                // Duplicate element found at 'mid'
                return nums[mid];
                
            } else if (nums[mid] == nums[mid - 1]) {
                // Element at 'mid' is duplicate of element at 'mid - 1'
                if (mid % 2 == 0) {
                    // even 'mid' => so 'mid' is after the location of
                    // unique element. Search to left
                    hi = mid - 2;
                } else {
                    // odd 'mid' => so 'mid' is prior the location of
                    // unique element. Search to right
                    lo = mid + 1;
                }
                
            } else { // nums[mid] == nums[mid + 1]

                // Element at 'mid + 1' is duplicate of element at 'mid'
                if (mid % 2 == 0) {
                    // even 'mid' => so 'mid' is prior to the location of
                    // unique element. Search to right
                    lo = mid + 2;
                } else {
                    // odd 'mid' => so 'mid' is after the location of
                    // unique element. Search to left
                    hi = mid - 1;
                }
            }
            
        }
        
        // Shouldn't reach here. Unique element not found
        return -1;
    }
};
