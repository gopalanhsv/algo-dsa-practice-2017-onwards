// nr => num matrix rows, nc => num matrix cols

// Binary search approach
// Time complexity : O(nrlognc)
// Space complexity : O(1)

// ZigZag traversal approach
// Time complexity : O(nr + nc)
// Space complexity : O(1)

/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int row, int col);
 *     vector<int> dimensions();
 * };
 */

class Solution {
public:
    int
    leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        // Get matrix dimensions and initialize
        auto matDimV = binaryMatrix.dimensions();
        _nRows = matDimV[0];
        _nCols = matDimV[1];
        
        //return leftMostColumnViaPerRowBinarySearch(binaryMatrix);
        return leftMostColumnViaZigZagTraversal(binaryMatrix);
    }
    
private:
    
    int
    leftMostColumnViaZigZagTraversal(BinaryMatrix& mat) {
        
        // Start at the top right corner of the matrix (last col).
        // 1. If that is a 0, there is no col with 1 in row 0; move down vertically
        // till a cell is reached with a 1 in row 'rx'. All the cells in rows
        // 0 to 'rx - 1' traversed vertically will not have a '1'.          
        // 2. If that is a 1, move left horizontally till a cell with 0 is hit
        // in col 'cx' or 0th column is reached => leftmost 1 in row 'rx' is at col
        // cx + 1; Now we need to check the other rows (rx + 1, last row) in column positions
        // (0 to cx) to find the leftmost 1 in matrix. Go to step 3
        // 3. If cell (rp, cp) is 0; move vertically down in column 'cp' till a
        // cell (rq, cp) with a 1 is hit.
        // 4. If cell (rp, cp) is 1; move horizontally left in row 'rp' till a
        // cell (rp, cq) with a 0 is hit. Leftmost 1 is at col 'cq'. Go to step 3
        

        auto c = _nCols - 1;
        auto r = 0;
        auto leftMostCol = _nCols;        
        // Loop till either all rows or all cols are explored
        while ((r < _nRows) && (c >= 0)) {
            if (1 == mat.get(r, c)) {
                // A 1 is hit at (r, c). Update leftmost col and move horizontally left
                // till a 0 is hit or matrix bounds crossed
                leftMostCol = c;
                --c;
            } else {
                // A 0 is hit at (r, c). Move vertically down till a 1 is hit or
                // matrix bounds crossed
                ++r;
            }
        }
        
        return (leftMostCol == _nCols) ? -1: leftMostCol;
    }
    
    int
    leftMostColumnViaPerRowBinarySearch(BinaryMatrix &binaryMatrix) {
        
        auto leftMostCol = _nCols;
        // Iterate over each row of matrix
        for (auto r = 0; r != _nRows; ++r) {
            // Find the leftmost column with a one
            // for current row via binary search
            auto currRowLeftMostCol = leftMostColWithOne(binaryMatrix, r);
            // Update the leftmost column to the minimum amongst those seen so far
            leftMostCol = min(currRowLeftMostCol, leftMostCol);
        }
        
        return (leftMostCol == _nCols) ? -1: leftMostCol;
    }

    int
    leftMostColWithOne(BinaryMatrix& mat, int row) {
        
        if (0 == mat.get(row, _nCols - 1)) {
            // No 1's in current row as last col is 0
            // Return an invalid col value
            return _nCols;
        }
        
        // Binary search range [lo, hi]
        int lo = 0, hi = _nCols - 1;
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (1 == mat.get(row, mid)) {
                // Col 'mid' is 1 => Sets new upper bound of search range.
                // Search lower cols
                hi = mid;
            } else {
                // Col 'mid' is 0 => Set new lower bound of search range.
                // Search higher cols
                lo = mid + 1;
            }
        }
        
        // Search terminates at lo == hi => the lowest value
        // of col for which the matrix entry is 1 for current row
        return lo;
    }
    
    // Data members
    int _nRows;
    int _nCols;
};
