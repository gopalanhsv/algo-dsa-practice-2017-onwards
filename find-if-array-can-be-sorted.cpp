// n => nums.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    bool
    canSortArray(vector<int>& nums) {
        // Adjacent elements can be swapped only if they have identical parity
        // => Sorting via swapping is possible only amongst contiguous elements
        // placed in block having identical parity.
        // => Sorting is not possible otherwise (i.e. amongst non contiguous
        // elements/element blocks or those having different parity)
        
        // The above implies that contiguous elements having identical parity
        // can thought of as a sorted block. Sorting across blocks is not allowed
        // => for the array to be sorted via given operation the blocks themselves
        // should have be pre-sorted earlier by initial placement
        // => min element in each block should be greater than the max element
        // in the preceeding block
        
        int maxElementPrevBlock = numeric_limits<int>::min();
        int minElementCurrBlock = nums[0];
        int maxElementCurrBlock = nums[0];
        int currBlockParity = elementParity(nums[0]);
        for (auto & elem : nums) {
            auto parity = elementParity(elem);
            if (parity != currBlockParity) {
                // New block of elements commences here
                maxElementPrevBlock = maxElementCurrBlock;
                
                // Update current block parameters with that of the new block
                // commencing at the current element
                currBlockParity = parity;
                minElementCurrBlock = elem;
                minElementCurrBlock = elem;
            }
            
            minElementCurrBlock = min(minElementCurrBlock, elem);
            maxElementCurrBlock = max(maxElementCurrBlock, elem);
            
            if (minElementCurrBlock <= maxElementPrevBlock) {
                // Sorting invariant between current group and previous group smashed
                return false;
            }
        }
        
        return true;
    }
    
private:
    
    int
    elementParity(int n) {
        // Applying K & R technique of clearing the rightmost set bit in each iteration
        int parity = 0;
        while (n) {
            n &= (n - 1);
            ++parity;
        }
        return parity;
    }
};
