// Factorization solution
// Time complexity : O(logn)
// Space complexity : O(1)

// Bit trick solution
// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    bool
    isPowerOfFour(int n) {
        // Base case
        if (n <= 0) {
            return false;
        }
        
#ifdef STANDARD_LOGN_SOLUTION
        
        // Number and its remainders should be repeatedly divisibly by 4 
        // till only 1 remains at the end
        while (n % 4 == 0) {
            n = n >> 2;
        }
        
        return n == 1;
#endif
        
#define CONSTANT_TIME_SOLN
#ifdef CONSTANT_TIME_SOLN

        // For 'n' to be a power of 4, its binary representation should have only a
        // single bit set in a location which is represents 4 ^ 0 or 4 ^ 1 or 4 ^ 2
        // or 4 ^ 3 or 4 ^ 4 and so on
        // i.e. 2 ^ 0, 2 ^ 2, 2 ^ 4, 2 ^ 6, 2 ^ 8 and so on 
        // i.e (1 << 6) | (1 << 4) | (1 << 2) | 1
        unsigned char bitMaskOf4PowersIn8Bits = 0x55;
        unsigned int bitMaskOf4PowersIn32Bits = 0x55555555;

        if (n & ~bitMaskOf4PowersIn32Bits) {
            return false;
        }
        // Check that only a single bit is set in the number
        // (flip rightmost bit using K&R trick and check if number becomes 0)
        return (n & (n - 1)) == 0;
        
#endif
        
    }
};
