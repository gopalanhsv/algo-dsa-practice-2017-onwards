// Time complexity : O(n! x n)
// Space complexity : O(n)

class Solution {
public:
    vector<vector<int>>
    permute(vector<int>& nums) {
        if (nums.empty()) {
            // Base case of single element/empty array
            return vector<vector<int>>();
        }
        
        // Generate all the permutations via DFS and backtracking
        generatePermutationsViaDfs(nums);
        
        return _allPermutationsV;
    }
    
private:
    
    void
    genPermutationsViaDfsRecursive(vector<int>& nums, bitset<16>& permIndicesTbl) {
        
        if (_currPermutationV.size() == _nElems) {
            // Current permutation is a complete one of all elements from original array
            _allPermutationsV.emplace_back(_currPermutationV);
            return;
        }
        
        // Current permutation is not yet complete
        // Add a new element from original array to the current permutation being built
        // Iterate over each element of nums sequentially
        for (int idx = 0; idx < _nElems; ++idx) {
            
            if (0 == permIndicesTbl[idx]) {
                // Element in 'nums' at index 'idx' is not yet added to current permutation
                // Add the element in 'nums' at index 'idx' to current permutation
                permIndicesTbl[idx] = 1;
                _currPermutationV.emplace_back(nums[idx]);
                // Permute the remaining elements of 'nums' via DFS recursively 
                genPermutationsViaDfsRecursive(nums, permIndicesTbl);
                // Backtrack and remove the element at 'idx' from current permutation
                _currPermutationV.pop_back();
                permIndicesTbl[idx] = 0;
            }
        }
    }
    
    void
    generatePermutationsViaDfs(vector<int>& nums) {
        _nElems = nums.size();
        // Hash table/bitset tracking indices of elements
        // added to the current permutation being built
        bitset<16> permIndicesTbl;
        // Generate all permutations recursively via DFS+backtracking
        genPermutationsViaDfsRecursive(nums, permIndicesTbl);
    }

    // Data members
    // Final number of elems in a permutation
    int _nElems;
    // Array of all permutations generated so far
    vector<vector<int> > _allPermutationsV;
    // Current permutation being generated
    vector<int> _currPermutationV;
};
