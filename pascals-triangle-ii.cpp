// Time complexity : O(rowIdx ^ 2)
// Space complexity : O(rowIdx)

class Solution {
public:
    vector<int>
    getRow(int rowIdx) {
        //return pascalTriangleRowMemoization(rowIdx);
        return pascalTriangleRowIterative(rowIdx);
    }
    
private:
    int
    pascalTriangleRecursive(
        int r, int c, vector<vector<int> >& ptTbl) {

        // If PT value for given r, c already computed in Table,
        // return it
        if (ptTbl[r][c] != -1) {
            return ptTbl[r][c];
        }
        
        // Compute PT value recursively
        // With 0 based indexing
        // PT(r, c) = 1, if c = 0 or r = c
        // PT(r, c) = PT(r - 1, c - 1) + PT(r - 1, c)
        if (0 == c || r == c) {
            ptTbl[r][c] = 1;
        } else {
            ptTbl[r][c] =
                pascalTriangleRecursive(r - 1, c - 1, ptTbl) +
                pascalTriangleRecursive(r - 1, c, ptTbl); 
        }
        
        return ptTbl[r][c];
    }
    
    vector<int>
    pascalTriangleRowMemoization(int r) {
        
        // Init pascal triangle memoization
        // table with all -1s (will use 0 based indexing) 
        vector<vector<int> > pascalTriangleTbl(r + 1, vector<int>(r + 1, -1));
        
        // Compute all columns of pascal triangle recursively for row 'r'
        int maxColIdx = r;
        for (int c = 0; c <= maxColIdx; ++c) {
            pascalTriangleRecursive(r, c, pascalTriangleTbl);
        }

        return pascalTriangleTbl[r];
    }
    
    vector<int>
    pascalTriangleRowIterative(int maxRowIdx) {
        
        int maxColIdx = maxRowIdx;
        vector<int> ptTbl(maxColIdx + 1, 1);
        
        for (int r = 0; r <= maxRowIdx; ++r) {
            
            int maxColIdxForRow = r;
            
            // Key insight here is to move from last column to first (i.e 0th column)
            // during computing; as PT value at a column depends on PT vals at lower
            // columns (not higher). Moving in this fashion prevents newly computed
            // values (in this row iteration instance) from being overwritten
            for (int c = maxColIdxForRow; c >= 0; --c) {    
                // PT(r, c) = 1, if c = 0/r
                // PT(r, c) = PT(r - 1, c - 1) + PT(r - 1, c)
                if (c == 0 || c == r) {
                    ptTbl[c] = 1;
                } else {
                    ptTbl[c] = ptTbl[c - 1] + ptTbl[c];
                }
            }
        }
        
        return ptTbl;
        
    }
};
