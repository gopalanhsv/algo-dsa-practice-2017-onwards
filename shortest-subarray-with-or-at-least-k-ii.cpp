// n => nums.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    int
    minimumSubarrayLength(vector<int>& nums, int k) {
        
        // Each selected subarray is modelled using a sliding window
        
        // Tracks the OR of all elements within the subarray/window
        int sWinAllElemsOr = 0;
        // bitPosToCnt[x] is the count of numbers within the subarray having
        // a set bit at position 'x' from LSB (LSB is at position 0)
        int nBits = 8 * sizeof(int);
        vector<int> bitPosToCntTbl(nBits, 0);

        int arrSz = nums.size();
        int subArrStart = 0;
        int minSubArrSz = arrSz + 1;
        // Iterate over the array sequentially from L->R adding the new
        // element to the subarray at each step
        for (auto subArrEnd = 0; subArrEnd < arrSz; ++subArrEnd) {
            auto currElem = nums[subArrEnd];
            sWinAllElemsOr |= currElem;
    
            addElemBitsToTbl(currElem, bitPosToCntTbl);
            
            while ((subArrStart <= subArrEnd) && (sWinAllElemsOr >= k)) {
                int subArrSz = subArrEnd - subArrStart + 1;
                minSubArrSz = min(minSubArrSz, subArrSz);
                // Remove the element at front of subarray/window 
                // and shrink the subarray from left
                int subArrStartElem = nums[subArrStart++];
                int removedBitMask =
                    removeElemBitsFromTbl(subArrStartElem, bitPosToCntTbl);
                
                // Clear all the bits 
                sWinAllElemsOr &= ~(removedBitMask);
            }
        }
        
        return (minSubArrSz == arrSz + 1) ? -1 : minSubArrSz;
    }
    
private:
    
    inline void
    addElemBitsToTbl(int elem, vector<int> & bitPosToCntTbl) {
        int bitPos = 0;
        while (elem > 0) {
            if (elem & 0x1) {
                ++bitPosToCntTbl[bitPos];
            }
            ++bitPos;
            elem >>= 1;
        }
    }
    
    inline int
    removeElemBitsFromTbl(int elem, vector<int> & bitPosToCntTbl) {
        int bitPos = 0;
        int removedBitMask = 0;
        while (elem) {
            if (elem & 0x1) {
                --bitPosToCntTbl[bitPos];
                if (0 == bitPosToCntTbl[bitPos]) {
                    removedBitMask |= (1 << bitPos);
                }
            }
            ++bitPos;
            elem >>= 1;
        }
        
        return removedBitMask;
    }
};
