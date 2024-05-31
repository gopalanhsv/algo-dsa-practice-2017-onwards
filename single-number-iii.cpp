// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    singleNumber(vector<int>& nums) {
        // Compute XOR of all array elements. Since all except 2 elements are duplicates,
        // duplicates XOR to 0 and remainder is the XOR of 2 unique elements
        int allElemsXor = 0;
        for (auto & num : nums) {
            allElemsXor ^= num;
        }
        auto & singleElemsXor = allElemsXor;
        
        // Determine the rightmost/least significant bit postion in
        // which the 2 unique elements differ
        int diffBitMask = 1;
        while (0 == (singleElemsXor & diffBitMask)) {
            diffBitMask <<= 1;
        }
        
        // Segregate array elements into 1 group based on the least significant
        // differing bit between the 2 unique elements and XOR group elements
        // All elements except the unique element are duplicate and cancel out leaving
        // one of the unique elements
        int allElemsXorWithDiffBit = 0;
        for (auto & num : nums) {
            if (num & diffBitMask) {
                allElemsXorWithDiffBit ^= num;
            }
        }
        auto & singleElem1 = allElemsXorWithDiffBit;
        // Compute the other unique element
        auto singleElem2 = singleElem1 ^ singleElemsXor;
        
        return {singleElem1, singleElem2};
    }
};
