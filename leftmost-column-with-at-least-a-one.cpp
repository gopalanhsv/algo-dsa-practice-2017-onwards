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
        // in col 'cx' or 0th column is reached => leftmost 1 in row 0 is at col
        // cx + 1; Now we need to check the other rows (1, last row) in column positions
        // (0 to cx) to find the leftmost 1 in matrix. Go to step 3
        // 3. If cell (rp, cp) is 0; move vertically down in column 'cp' till a
        // cell (rq, cp) with a 1 is hit.
        // 4. If cell (rp, cp) is 1; move horizontally left in row 'rp' till a
        // cell (rp, cq) with a 0 is hit. Leftmost 1 is at col 'cq'. Go to step 3
        

        int c = _nCols - 1;
        int r = 0;
        int leftMostColIdx = _nCols;        
        // Loop till either all rows or all cols are explored
        while ((r < _nRows) && (c >= 0)) {
            if (1 == mat.get(r, c)) {
                // A 1 is hit at (r, c). Update leftmost col and
                // move horizontally left till a 0 is hit or matrix
                // bounds crossed
                leftMostColIdx = c;
                --c;
            } else {
                // A 0 is hit at (r, c). Move vertically down till
                // a 1 is hit or matrix bounds crossed
                ++r;
            }
        }
        
        return (leftMostColIdx == _nCols) ? -1: leftMostColIdx;
    }
    
    int
    leftMostColumnViaPerRowBinarySearch(BinaryMatrix &binaryMatrix) {
        
        int leftMostColIdx = _nCols;
        // Iterate over each row of matrix
        for (int r = 0; r != _nRows; ++r) {
            // Find the leftmost column with a one
            // for current row via binary search
            int rowLeftMostColIdx = findleftMostColWithOne(binaryMatrix, r);
            // Update the left most column with one
            // over each row to the minimum possible col
            leftMostColIdx = min(rowLeftMostColIdx, leftMostColIdx);
        }
        
        return (leftMostColIdx == _nCols) ? -1: leftMostColIdx;
    }
    
    
    int
    findleftMostColWithOne(BinaryMatrix& mat, int row) {
        
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
                // Col 'mid' is 1. This will now be the new upper bound
                // of the search range. Search in lower cols
                hi = mid;
            } else {
                // Col 'mid' is 0. This will now be the new lower bound
                // of search range. Search in higher cols
                lo = mid + 1;
            }
        }
        
        // Search terminates when lo == hi; which will the lowest value
        // of col for which the matrix entry is 1 for given row
        return lo;
    }
    
    // Data members
    int _nRows;
    int _nCols;
};
