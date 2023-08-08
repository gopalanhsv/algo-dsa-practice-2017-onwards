// Time complexity : O(log nums.size())
// Space complexity : O(1)

class Solution {
public:
    bool
    search(vector<int>& nums, int target) {
        
        if (nums.empty()) {
            // Base case of empty array
            return false;
        }
        
        if (nums.size() == 1) {
            // Base case of single element array
            return (nums[0] == target);
        }
        
        // Exec a binary search for the target
        return singlePassSearch(nums, target);
    }

    
private:
    
    bool
    singlePassSearch(vector<int>& v, int key) {
        
        int l = 0, r = v.size() - 1;
        
        // Key will lie (if it exists) in the closed range [l, r]
        
        while (l <= r) {
            
            int mid = l + (r - l) / 2;    
            if (v[mid] == key) {
                // Key found
                return true;
            }
            
            // Either [l, mid] range would be sorted or [mid, r] range would be sorted
            // In each iteration, narrow down the range for key search
            if (v[l] < v[mid]) {
                // [l, mid] range is sorted. If key lies in this range
                // then continue search here in [l, mid]. If key not in
                // this range, continue search outside this range in [mid + 1, r]
                if (v[l] <= key && key < v[mid]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else if (v[l] == v[mid]) {
                // [l, mid] has same values at range extremities
                // => 'key' may or may not be present in this range
                // Adjust search range by doing a linear search in range [l, mid] to
                // either exclude this range OR narrow down to a subrange within it
                while ((l < mid) && (v[l] == v[mid])) {
                    ++l;
                }
                if (l == mid) {
                    // Old [l, mid] is same value range throughout
                    // Exclude this range as this does not have the key
                    // Continue search in upper half of search range [mid + 1, r]
                    l = mid + 1;
                }
                
            } else {
                // v[l] > v[mid]
                // [l, mid] range is unsorted. That implies [mid, r] range is sorted
                // Check if key lies in [mid, r] range. If yes, continue search
                // in [mid, r]; otherwise continue search in [l, mid - 1]
                if (v[mid] < key && key <= v[r]) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
        }
        
        return false;
    }
    
};
