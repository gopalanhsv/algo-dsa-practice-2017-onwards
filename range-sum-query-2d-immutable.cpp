// Time complexity
// O(num rows x num cols)
// Space complexity
// O(num rows x num cols)

#if 1
class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        
        // Construct matrix holding lower right sum for each [r, c]
        int nr = matrix.size();
        int nc = matrix[0].size();
        _lowerRightSumMatrix.resize(nr + 1, vector<int>(nc + 1, 0));
        
        for (int r = 0; r != nr; ++r) {
            int currRowPrefixSum = 0;
            for (int c = 0; c != nc; ++c) {
                currRowPrefixSum += matrix[r][c];
                // Entry would be current running row sum
                // plus preceeding row sum for same column
                _lowerRightSumMatrix[r + 1][c + 1] = 
                    currRowPrefixSum + _lowerRightSumMatrix[r][c + 1];
            }
        }
    }
    
    int
    sumRegion(int row1, int col1, int row2, int col2) {
        
        // Sum of elements in the rectangle above the given range
        // i.e from (0, 0) to (row1 - 1, col2)
        int upperRectangleSum = _lowerRightSumMatrix[row1][col2 + 1];
        // Sum of elements in the rectangle to left of the given range
        // i.e from (0, 0) to (row2, col1 - 1)
        int leftRectangleSum = _lowerRightSumMatrix[row2 + 1][col1];
        // Sum of elements in the rectangle to upper left of the given range
        // i.e from (0, 0) to (row1 - 1, col1 - 1)
        int upperLeftRectangleSum = _lowerRightSumMatrix[row1][col1];
        
        // Sum of elements in the rectangle at lower right of the given range
        // i.e from (0, 0) to (row2, col2)
        int lowerRightSum = _lowerRightSumMatrix[row2 + 1][col2 + 1];
        
        return 
            lowerRightSum - (upperRectangleSum + leftRectangleSum) + upperLeftRectangleSum;
    }
    

private:
    
    // Num rows & cols of the matrix
    int _nr;
    int _nc;
    
    // Lower right sum Matrix which holds sum of all elems of submatrix
    // having upper right diagonal at (0, 0) and lower right diagonal
    // at given row, column entry including that entry. Using 1 based
    // indexing here to avoid checks for 0th row/column in code
    vector<vector<int> > _lowerRightSumMatrix;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */

#endif

#if 0
class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        
        // Construct matrix holding left top range sum for each [r, c]
        unsigned int nRows = matrix.size();
        unsigned int nCols = matrix[0].size();
        _leftTopSumMatrix = 
            vector<vector<int> >(nRows + 1, vector<int>(nCols + 1, 0));
        for (unsigned int r = 0; r != nRows; ++r) {
            long currRowElemsSum = 0;
            for (unsigned int c = 0; c != nCols; ++c) {
                currRowElemsSum += matrix[r][c];
                // Entry would be current running row sum
                // plus earlier row sum for same column
                _leftTopSumMatrix[r + 1][c + 1] =
                    currRowElemsSum + _leftTopSumMatrix[r][c + 1];
            }
        }
        
    }
    
    int
    sumRegion(int row1, int col1, int row2, int col2) {
    
        long bottomRightSum = _leftTopSumMatrix[row2 + 1][col2 + 1];
        long bottomLeftMatrixSum = _leftTopSumMatrix[row2 + 1][col1];
        long upperRightMatrixSum = _leftTopSumMatrix[row1][col2 + 1];
        long upperLeftMatrixSum = _leftTopSumMatrix[row1][col1];
        
        return bottomRightSum - 
            (bottomLeftMatrixSum + upperRightMatrixSum - upperLeftMatrixSum);
        
    }
    
private:
    
    // Sum Matrix which holds sum of all elems of submatrix to left
    // and top of a row, column entry including that entry. Using 1 based
    // indexing here to avoid checks for 0th row/column in code
    vector<vector<int> > _leftTopSumMatrix;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
#endif
