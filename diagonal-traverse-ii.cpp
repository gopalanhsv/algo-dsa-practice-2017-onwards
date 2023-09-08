// Time complexity : O(num array elements) / O(n)
// Space complexity : O(num array elements) / O(n)

class Solution {
public:
    vector<int>
    findDiagonalOrder(vector<vector<int>>& nums) {
        
        int nRows = nums.size();
        // Sum of row and column indices for each diagonal are the same
        // So group all diagonal element together at the same location in the
        // hash table mapped via diagonal id
        unordered_map<int, vector<int> > diagonalElemsTbl;
        int maxDiagonalId = 0;
        // Iterate over the matrix from the bottom to the top row in row major fashion 
        // (this ensures that elements belonging to same diagonal are grouped in 
        // accordance to bottom to top/ left to right traversal)
        for (int r = nums.size() - 1; r >= 0; --r) {
            // Iterate over each element in the current row from L->R sequentially
            // placing elements belonging to the same diagonal (as per diagonal id)
            // at the same location in the hash table
            int numCols = nums[r].size();
            for (int c = 0; c != numCols; ++c) {
                int diagonalId = r + c;
                maxDiagonalId = max(maxDiagonalId, diagonalId);
                diagonalElemsTbl[diagonalId].emplace_back(nums[r][c]);
            }
        }
            
        vector<int> outV;
        int maxCols = 0;
        // Iterate over each diagonal in sequence (from top left to bottom right)
        for (int diagonalId = 0; diagonalId <= maxDiagonalId; ++diagonalId) {
            auto iter = diagonalElemsTbl.find(diagonalId);
            if (iter != diagonalElemsTbl.end()) {
                auto & diagonalElemsV = iter->second;
                // Copy all elements of current diagonal to output array
                copy(diagonalElemsV.begin(), diagonalElemsV.end(), back_inserter(outV));
            }
        }
        
        return outV;
    }
};
