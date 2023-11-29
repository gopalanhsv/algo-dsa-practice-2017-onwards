// Rightmost bit flip Approach
// Time complexity : O(log n)
// Space complexity : O(1)

// Precomputed Table Approach
// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    int
    hammingWeight(uint32_t n) {
        //return hammingWeightViaRightmostBitFlip(n);
        return hammingWeightViaPrecomputedTable(n);
    }
    
private:
    
    int
    hammingWeightViaRightmostBitFlip(uint32_t n) {
        // Compute hamming weight by progressively reducing 'n'
        // by AND'ing with equivalent 'n - 1'. This will flip the
        // rightmost bit/LSB to 0
        uint32_t hw = 0;
        while (n) {
            ++hw;
            n &= (n - 1);
        }
        
        return hw;
    }
    
    int
    hammingWeightViaPrecomputedTable(uint32_t n) {
        // Table mapping numbers from 0 to 15 (i.e. max 4 bits) to their
        // respective bit count
        vector<uint32_t> parityTbl = {
            0, // 0
            1, // 1
            1, // 2
            2, // 3
            1, // 4
            2, // 5
            2, // 6
            3, // 7
            1, // 8
            2, // 9
            2, // 10
            3, // 11
            2, // 12
            3, // 13
            3, // 14
            4  // 15
        };
        
        // Break the number into consecutive 4 bit blocks and count the
        // number of ones in each block using the lookup table above
        uint32_t bitMask = 0xF;
        uint32_t hammingWt = 0;
        for (uint32_t blkOffset = 0; blkOffset <= 28; blkOffset += 4) {
            hammingWt += parityTbl[((n >> blkOffset) & bitMask)];
        }
        return hammingWt;
    }
};
