// Time complexity : O(logn) n=> array length
// Space complexity : O(1)

/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
public:
    int
    findInMountainArray(int target, MountainArray &mountainArr) {
        // Do a triple binary search. One for partitioning array around peak.
        // Then 2 binary searches for 'target' in the partitions around peak
        // Prefer the left partiton over the right partition as it may have 
        // the minimum index
        int n = mountainArr.length();
        int lo = 0;
        int hi = n - 1;
                
        // Find array peak index location in range [lo, hi] via binary search
        int peakIdx = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int midVal = mountainArr.get(mid);
            // Element val @ mid - 1
            int priorToMidVal = numeric_limits<int>::min(); // VIMP else out of range error
            if (mid - 1 >= 0) {
                priorToMidVal = mountainArr.get(mid - 1);
            }
            // Element Val @ mid + 1
            int nextToMidVal = numeric_limits<int>::min(); // VIMP else out of range error
            if (mid + 1 < n) {
                nextToMidVal = mountainArr.get(mid + 1);
            }
            if ((midVal > nextToMidVal) && (midVal > priorToMidVal)) {
                // At/Found peak
                peakIdx = mid;
                break;
            } else if ((midVal < nextToMidVal) && (midVal > priorToMidVal)) {
                // In upslope/left of mountain peak
                // Search for peak towards right
                lo = mid + 1;
            } else {
                // In downslope/right of mountain peak
                // Search for peak towards left
                hi = mid - 1;
            }
        }
        
        // Target at the mountain peak
        if (mountainArr.get(peakIdx) == target) {
            return peakIdx;
        }
        
        // Search in the two partitions around array peak for given 'target'
        
        // Search in first half (left of mountain peak) for given 'target'
        // Increasing element range
        lo = 0;
        hi = peakIdx;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int midVal = mountainArr.get(mid);
            if (midVal == target) {
                // Found target
                return mid;
            } else if (midVal < target) {
                // Target lies to right of 'mid'. Search for target towards right
                lo = mid + 1;
            } else {
                // Target lies to left of 'mid'. Search for target towards left
                hi = mid - 1;
            }
        }
        
        // Search in second half (right of mountain peak) for given 'target'
        // Decreasing element range
        lo = peakIdx + 1;
        hi = n - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int midVal = mountainArr.get(mid);
            if (midVal == target) {
                // Found target
                return mid;
            } else if (midVal < target) {
                // Target lies to left of 'mid'. Search for target towards left
                hi = mid - 1;
            } else {
                // Target lies to right of 'mid'. Search for target towards right
                lo = mid + 1;
            }
        }
        
        // target not found in array
        return -1;
    }
};
