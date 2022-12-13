class Solution {
public:
    void
    nextPermutation(vector<int>& nums) {
        int arrSz = nums.size();
        if (arrSz < 2) {
            return;
        }
        
        // For a sequence in descending order, no larger permutation is possible
        // Next possible permutation is all elements of the sequence in ascending order

        // For other sequences, while moving from right to left, say the first peak
        // is at 'x'; then element a[x] to a[n - 1] are in descending order and
        // a[x - 1] is l.t a[x]
        // The next permutation for the current sequence with a[x - 1] < a[x] and 
        // a[x] > a[x + 1] > a[x + 2]... > a[n - 1]; would be found by moving the
        // immediate greater element to a[x - 1] in the range [x, n - 1] to the
        // location 'x - 1' and re-sorting the elements [x, n - 1] in ascending order
        // The above operation is alternatively done easily by finding the first
        // element a[j] g.t. a[x - 1] in the range [x, n - 1]; then swapping a[x - 1]
        // and a[j]. This leads to elements in [x, n - 1] be in descending order.
        // Finally do reversal of the range [x, n - 1]; leading to [x, n - 1] in
        // ascending order
        
        
        // Traverse from R->L. Find the first element lesser than its previous element
        int lo = 0, hi = arrSz - 1;
        for (int i = arrSz - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {
                // Now find first element in the range [i + 1, arrSz - 1]
                // greater than nums[i]
                int firstGtIdx = i + 1;
                while ((firstGtIdx + 1 < arrSz) && (nums[firstGtIdx + 1] > nums[i])) {
                    ++firstGtIdx;
                }
                // Swap elements
                swap(nums[i], nums[firstGtIdx]);
                lo = i + 1;
                break;
            }
        }
        
        // Reverse the sequence in the range [lo, arrSz - 1]
        while (lo < hi) {
            swap(nums[lo++], nums[hi--]);
        }
    }
};
