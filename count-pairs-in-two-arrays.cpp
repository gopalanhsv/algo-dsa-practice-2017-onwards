// n => nums1/nums2.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {
public:
    long long
    countPairs(vector<int>& nums1, vector<int>& nums2) {
        // Pairs obey the foll. constraint:
        // nums1[i] + nums1[j] > nums2[i] + nums2[j] for i < j
        // => (nums1[i] - nums2[i]) + (nums1[j] - nums2[j]) > 0 for i <  j

        // If a difference vector diffV[x] = nums1[x] - nums2[x] is built,
        // then at an index 'j', pairs are formed with all prior indices i < j 
        // for which diff1V[i] + diff2V[j] > 0
        // diff1V[i] + diff2V[j] = diff1V[j] + diff2V[i] => pairs with i != j
        // are all that matter
        
        // Need to look for pairs with diff1V[i] + diff2V[j] > 0; i != j
        // Easily done by sorting the diffV array and applying 2 pointer
        // method to count pairs satifying the reqd condition
        
        auto arrSz = nums1.size();
        // Compute the differences 'nums1 - nums2' for each index and store it
        vector<int> diffsV(arrSz);
        for (auto j = 0; j < arrSz; ++j) {
            diffsV[j] = nums1[j] - nums2[j];
        }
        // Sort the differences in ascending order
        sort(diffsV.begin(), diffsV.end());

        long long nTotalPairs = 0;
        // Init 2 points to range ends ('lo'/'hi' may only be incremented/decremented)
        auto lo = 0;
        auto hi = arrSz - 1;
        while (lo < hi) {
            if (diffsV[lo] + diffsV[hi] > 0) {
                // All diffsV in range [lo, hi - 1] form pairs with diffsV[hi]
                // s.t their sum is g.t 0
                nTotalPairs += (hi - 1 - lo + 1);
                // All pairs with diffV[hi] accounted for. Reduce 'hi' to
                // search for new pairs
                --hi;
            } else {
                // Look for larger diffsV in range [lo + 1, hi - 1] to form pairs with diffsV[hi]
                // s.t their sum is g.t 0
                ++lo;
            }
        }
        return nTotalPairs;
    }
};
