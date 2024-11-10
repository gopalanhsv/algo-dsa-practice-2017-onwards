// Time Complexity : O(logn)
// Space Complexity : O(1)

class Solution {
public:
    long long
    minEnd(int n, int x) {
        long long minANDVal = x;
        
        // Number whose bits are to be merged to the locations of only '0's
        // in the minimum AND value i.e. 'x' (from LSB to MSB)
        unsigned long numToBeMerged = n - 1;
        long long minLastVal = 0;
        int bitPos = 0;
        while (minANDVal) {
            long long mask = (1LL << bitPos);
            
            if (numToBeMerged) {
                if (0 == (minANDVal & 0x1)) {
                    if (numToBeMerged & 0x1) {
                        minLastVal |= mask;
                    }
                    numToBeMerged >>= 1;
                }
            } 
            
            if (1 == (minANDVal & 0x1)) {
                minLastVal |= mask;
            }

            minANDVal >>= 1;
            ++bitPos;
            
        }
        
        minLastVal |= (numToBeMerged << bitPos);
        
        return minLastVal;
    }
};
