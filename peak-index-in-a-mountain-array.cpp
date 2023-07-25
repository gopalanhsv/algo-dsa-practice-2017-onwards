// Time complexity : O(log arr.size())
// Space complexity : O(1)

class Solution {
public:
    int
    peakIndexInMountainArray(vector<int>& arr) {
        // With the given constraints of min 3 elems, all elements being unequal, and array
        // elements guaranteed to be arranged in mountain format, employ binary search
        int l = 0, r = arr.size() - 1;
        
        // l & r will converge at peak point with l == r
        while (l < r) {
            // Compute mid point
            int mid = l + ((r - l) / 2);
                  
            if (arr[mid] > arr[mid + 1]) {
                // mid + 1 lies on descending part of mountain
                // So peak lies in lower half of search range to left of mid + 1
                r = mid;
            } else {
                // arr[mid] < a[mid + 1]
                // mid lies on ascending part of mountain array
                // So peak lies in upper half of search range to right of mid
                l = mid + 1;
            }
        }
        
        // l and r converge at peak in a pincer movement
        return l;
    }
};
