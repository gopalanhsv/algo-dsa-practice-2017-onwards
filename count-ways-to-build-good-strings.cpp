// Time complexity : O(high)
// Space complexity : O(high)

class Solution {
public:
    int
    countGoodStrings(int low, int high, int zero, int one) {
        return countGoodStringsBottomUpDP(low, high, zero, one);
    }
    
private:
    
    int
    countGoodStringsBottomUpDP(int lo, int hi, int nZeros, int nOnes) {
        const int moduloFactor = 1000000000 + 7;
        
        // nWaysTbl[i] => num ways to build strings of length 'i'
        // ending with either 0 or 1 by appending either 'nZeros' 0 or
        // 'nOnes' 1 at each step
        vector<long> nWaysTbl(hi + 1, 0);
        // Empty string can be built only in a single way
        nWaysTbl[0] = 1;
        for (int strLen = 1; strLen <= hi; ++strLen) {
            // There are two options to build strings of length 'strLen':-
            // 1. By appending 'nZeros' zeroes at the end
            // of string of length 'strLen - nZeros'
            if (strLen - nZeros >= 0) {
                nWaysTbl[strLen] += nWaysTbl[strLen - nZeros];
            }
            // 2. By appending 'nOnes' ones at the end
            // of string of length 'strLen - nOnes'
            if (strLen - nOnes >= 0) {
                nWaysTbl[strLen] += nWaysTbl[strLen - nOnes];
            }
            
            // Normalize count to modulo factor range
            nWaysTbl[strLen] %= moduloFactor;
        }
        
        // Count the number of ways in which string of
        // length [lo, hi] can be built
        long nWays = accumulate(nWaysTbl.begin() + lo, nWaysTbl.end(), 0L);
        
        return nWays % moduloFactor;
    }
};
