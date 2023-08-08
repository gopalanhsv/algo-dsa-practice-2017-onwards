// Time complexity : O(log(nums.size()))
// Space complexity : O(1)

class Solution {
public:
    int
    search(vector<int>& nums, int target) {
        
        if (nums.empty()) {
            // Base case of empty array
            return -1;
        }
        
        if (nums.size() == 1) {
            // Base case fo single element array
            return (nums[0] == target) ? 0 : -1;
        }
        
        // Binary search for target
        return singlePassSearch(nums, target);   
    }
    
private:
    
    int
    singlePassSearch(vector<int>& v, int key) {
        
        int l = 0, r = v.size() - 1;
        if (v[l] <= v[r]) {
            // [l, r] range is sorted
            if (key < v[l] || key > v[r]) {
                // key not in range
                return -1;
            }
        }
        
        // Invariant : Key will always lie (if it exists) in closed range [l, r]
        while (l <= r) {
            
            int mid = l + (r - l) / 2;
            if (v[mid] == key) {
                // Key found
                return mid;
            }
            
            // Either [l, mid] range would be sorted or [mid, r] range would be sorted
            // In each iteration, narrow down the search range
            
            if (v[l] <= v[mid]) {
                // [l, mid] range is sorted
                if (v[l] <= key && key < v[mid]) {
                    // Key lies in range [l, mid - 1]. Continue search in [l, mid - 1]
                    r = mid - 1;
                } else {
                    // Key does not lie in range [l, mid]. Continue search outside
                    // in upper part of the range [mid + 1, r]
                    l = mid + 1;
                }
            } else {
                // [l, mid] range is unsorted => [mid, r] range is sorted
                if (v[mid] < key && key <= v[r]) {
                    // Key lies in range [mid + 1, r]. Continue search in [mid + 1, r]
                    l = mid + 1;
                } else {
                    // Key does not lie in range [mid + 1, r]. Continue search outside
                    // in lower part of the range [l, mid - 1]
                    r = mid - 1;
                }
                
            }
        }
        
        return -1;
    }
    
};
