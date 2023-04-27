// Time complexity : O(flips.size())
// Space complexity : O(1)

class Solution {
public:
    int
    numTimesAllBlue(vector<int>& flips) {
        int n = flips.size();
        
        // Since flips is a permutation of 'n' integers in the range [1, n],
        // each element would be unique ranging from 1 to n
        // Since toggling of a bit in the 1-indexed string (of length 'n' which is
        // initially all 0's) is as per the indices specified in 'flips', each bit
        // will be toggled only once to 1
        
        // For prefix-alignment at a step 'i', bits of the string which are toggled
        // as per the subarray flips[0, i - 1] should be s.t that bits[0, i - 1]
        // are all 1's and bits[i, n - 1] are 0's
        // => subarray flips[0, i - 1] should toggle the bits [0, i - 1] of the string
        // => 'i' entries of subarray flips[0, i - 1] should correspond to the 'i' bit
        //    positions closed range [0, i - 1] of the string; i.e the initial bit
        //    positions 0, 1, 2, ..., i - 1
        // => 'i' entries of subarray flips[0, i - 1] should be a permutation of the
        //    numbers in the closed range [1, i]
        
        // The above boils down to the fact that for prefix alignment at step 'i',
        // flips [0, i - 1] should be a permutation of integers [1, i]
        // The above can easily be determined comparing sum of entries in
        // flips [0, i - 1] with AP progression sum [1, i]
        long long prefixSum = 0;
        long long apSum = 0;
        int nPrefixAlignments = 0;
        for (int i = 1; i <= n; ++i) {
            prefixSum += flips[i - 1];
            apSum += i;
            if (apSum == prefixSum) {
                ++nPrefixAlignments;
            }
        }
        
        return nPrefixAlignments;
    }
};
