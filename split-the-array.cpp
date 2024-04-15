// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    bool
    isPossibleToSplit(vector<int>& nums) {
        if (nums.empty() || (1 == nums.size() & 0x1)) {
            // Array cannot be split as reqd if it has odd number of elements or empty
            return false;
        }
        
        // Array has even number of elements => elements can be distributed
        // amongst two equal sized arrays
        
        // Check for new arrays to possess only distinct elements
        unordered_map<int, int> freqCntTbl;
        // Iterate over each array element
        for (auto & e : nums) {
            if (++freqCntTbl[e] > 2) {
                // Current elemnt has a frequency count over 2 => it will occur
                // mpre than once in an array post split
                return false;
            }
        }
        
        return true;
    }
};
