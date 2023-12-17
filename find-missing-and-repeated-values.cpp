// n => grid.size()
// Time complexity : O(n x n)
// Space complexity : O(n x n)

class Solution {
public:
    vector<int>
    findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        return hashTableApproach(grid);
    }

private:
    vector<int>
    hashTableApproach(vector<vector<int>>& grid) {
        // Num rows/cols
        auto n = grid.size();
        int duplicateElem;
        // Iterate over all elements and store in them in hash table
        unordered_set<int> elemsTbl;
        for (auto r = 0; r != n; ++r) {
            for (auto c = 0; c != n; ++c) {
                // Current element
                auto & ce = grid[r][c];
                if (elemsTbl.find(ce) != elemsTbl.end()) {
                    // Current element is the duplicate element
                    duplicateElem = ce;
                }
                elemsTbl.insert(ce);
            }
        }
        
        // Grid of size 'n x n' should contain all elements from [1, n ^ 2]
        // but due to presence of duplicate element, there is a missing one
        // Iterate over all elements in range [1, n ^ 2].
        auto lastElem = n * n;
        int missingElem;
        for (auto e = 1; e <= lastElem; ++e) {
            if (elemsTbl.find(e) == elemsTbl.end()) {
                // Element which is not present in the hash table is the missing one
                missingElem = e;
                break;
            }
        }
        
        return {duplicateElem, missingElem};
    }
};
