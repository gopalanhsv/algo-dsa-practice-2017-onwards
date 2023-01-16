/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     // Compares the sum of arr[l..r] with the sum of arr[x..y] 
 *     // return 1 if sum(arr[l..r]) > sum(arr[x..y])
 *     // return 0 if sum(arr[l..r]) == sum(arr[x..y])
 *     // return -1 if sum(arr[l..r]) < sum(arr[x..y])
 *     int compareSub(int l, int r, int x, int y);
 *
 *     // Returns the length of the array
 *     int length();
 * };
 */

class Solution {
public:
    int
    getIndex(ArrayReader &reader) {
        // Problem reduces to a simple binary search
        // In each iteration, eliminate a half of the search range
        // which contains only equal elements
        
        int arrSz = reader.length();
        
        int lo = 0;
        int hi = arrSz - 1;
        // Exec a bin search in the range [lo, hi] till either the
        // larger element is found OR the range converges to a single element
        while (lo < hi) {

            int rangeSz = hi - lo + 1;
            int mid = lo + rangeSz / 2;
            
            if (1 == (rangeSz & 0x1)) {
                // Odd sized range [lo, hi]
                // [lo, mid - 1] & [mid + 1, hi] will the 2 equal halves
                // [mid, mid] will be the range middle element
                int compVal = reader.compareSub(lo, mid - 1, mid + 1, hi);
                if (compVal == 0) {
                    // Range sum [lo, mid - 1] equals that of [mid + 1, hi]
                    // i.e. [mid, mid] has the largest integer
                    return mid;
                } else if (compVal == 1) {
                    // Range sum [lo, mid - 1] exceeds that of [mid + 1, hi]
                    // i.e. [lo, mid - 1] has the largest integer
                    hi = mid - 1;
                } else {
                    // Range sum [lo, mid - 1] is lesser than that of [mid + 1, hi]
                    // i.e. [mid + 1, hi] has the largest integer
                    lo = mid + 1;
                }
            } else {
                // Even sized range [lo, hi]
                // [lo, mid - 1] & [mid, hi] will the 2 equal halves
                if (reader.compareSub(lo, mid - 1, mid, hi) == 1) {
                    // Range sum [lo, mid - 1] exceeds that of [mid, hi]
                    // i.e. [lo, mid - 1] has the largest integer
                    hi = mid - 1;
                } else {
                    // Range sum [lo, mid - 1] is lesser than that of [mid, hi]
                    // i.e. [mid, hi] has the largest integer
                    lo = mid;
                }
            }
        }
        
        // Search range converges to a single element. That would be
        // the required largest element
        return lo;
    }
};
