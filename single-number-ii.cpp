// Time complexity : O(nums.size() x (num bits))
// Space complexity : O(1)

class Solution {
public:
    int
    singleNumber(vector<int>& nums) {
        return singleNumberViaModuloOps(nums);   
    }
    
private:
    
    int
    singleNumberViaModuloOps(vector<int>& nums) {
        // n nums, every element occurs 3 times except for
        // 1 which is of single occurence
        // Since we need to find only the element having a single
        // occurrence, the requirements are as following:-
        // 1. '1' bits at bit positions which occur only the elements having 3 occurences
        //     and NOT IN element with single occurence should be cleared to '0' in
        //     the final result
        // 2. '1' bits at bit positions which occur only the elements having 3 occurences
        //     and IN element with single occurence should be set to '1' in
        //     the final result
        // 3. '0' bits at bit positions which occur both in the elements having 3 occurences
        //     and single occurence should be cleared to '0' in the final result
        
        // Requirements 1 & 2 lead to the fact that if we count the number of set bits
        // at a particular bit position across all numbers
        // 1. the count being a multiple of 3 => that bit is set only in elements
        //    with multiple occurrence count and not in the element with single occurence count
        // 2. the count being not a multiple of 3 => that bit is set in element
        //    in the element with single occurence count
        // 3. the count being 0 => that bit is not set in element
        //    in the element with single occurence count
        // In effect, if the count of set bits at a particular bit position across all given
        // elements is divisible by 3, the bit should be set to 0 in the single occurence
        // element; otherwise it should be set to 1
        
        int singleOccurenceElem = 0;
        int nBits = 8 * sizeof(singleOccurenceElem);
        // Iterate over each bit position
        for (int bitPos = 0; bitPos != nBits; ++bitPos) {
            int nSetBitCnt = 0;
            // Iterate over each number and count the occurences of '1's at
            // bit position 'bitPos' across all numbers
            for (auto num : nums) {
                nSetBitCnt += ((num >> bitPos) & 0x1);
            }
            
            if (0 != nSetBitCnt % 3) {
                // Count of set bits is not a multiple of 3 and hence occurs in single element
                singleOccurenceElem |= (1 << bitPos);
            }
        }
        
        return singleOccurenceElem;
    }
};
