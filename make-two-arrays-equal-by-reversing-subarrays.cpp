// n => target.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    bool
    canBeEqual(vector<int>& target, vector<int>& arr) {
        if (target.size() != arr.size()) {
            // Error check
            return false;
        }
        
        // Making 'arr' equal to 'target' by reversing any sub-array any number of
        // times includes swapping two adjacent elements => variation of bubble sort
        // => array 'arr' can be made equal to 'target' iff both have identical elements
        
        // Checking 2 arrays for identical elements can be done either via sorting or
        // hash table
        // Using hash table here as it has O(n)/On(n) time/space complexity compared
        // to sorting  which has O(nlogn)/On(n) time/space complexity.
        
        // Populate frequency count table for array 'arr' elements
        vector<int> freqCntTbl(1001, 0);
        for (auto & x : arr) {
            freqCntTbl[x]++;
        }
        
        // Check if all elements of 'target' are present in 'arr'
        // frequency count table
        for (auto & x : target) {
            if (freqCntTbl[x] > 0) {
                --freqCntTbl[x];
            } else {
                return false;
            }
        }
        
        return true;
    }
};
