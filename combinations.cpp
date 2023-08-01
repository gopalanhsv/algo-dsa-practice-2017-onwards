// Time complexity : O(C(n, k))
// Space complexity : O(k) for stack, O(C(n, k)) for output array
class Solution {
    
public:
    vector<vector<int>>
    combine(int n, int k) {
        
        // Generate the set of valid combinations via
        // DFS and backtracking
        generateCombinationsDFS(n, k, 1);
        
        return _validCombinationsV;
    }
    
private:
    
    void
    generateCombinationsDFS(int n, int k, int startNum) {
        
        // Iterate over all numbers possible at this level
        for (int currNum = startNum; currNum <= n; ++currNum) {
            // Add current number to combination
            _currCombination.emplace_back(currNum);
            
            if (_currCombination.size() == k) {
                // Current combination has 'k' numbers and is a valid one.
                // Store in output. This will terminate recursion for this branch too
                _validCombinationsV.emplace_back(_currCombination);
            } else {
                // Attempt to form a valid combination with current number and maybe subsequent
                // nums (For next level start number would be the subsequent number as all
                // numbers have to be unique per combination)
                generateCombinationsDFS(n, k, currNum + 1);
            }
            
            // Backtrack and Remove current number from this combination
            _currCombination.pop_back();
        }
    }
    
    // Data members
    vector<vector<int> > _validCombinationsV; // Output vector of valid combinations
    vector<int> _currCombination; // Track current running combination
};
