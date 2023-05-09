// nr => num matrix rows, nc => num matrix cols
// Time complexity : O(nr x nc)
// Space complexity : O(nr x nc)

class Solution {
public:
    vector<vector<int>>
    spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        auto & nr = rows;
        auto & nc = cols;
        // Output vector of visited cells in spiral order
        int nCells = nr * nc;
        vector<vector<int> > visitedCellsV;
        
        // Demarcates the matrix boundary for the spiral
        // move at any point during execution
        int topRow = rStart;
        int leftCol = cStart - 1;
        int rightCol = cStart + 1;
        int bottomRow = topRow + 1;
        
        int nWrittenCells = 0;
        while (nWrittenCells < nCells) {
            int r = topRow;
            int c = leftCol + 1;
            // Fill top row of spiral from left to right
            if (isValidRow(r, nr)) {
                while ((nWrittenCells < nCells) && (c <= rightCol)) {
                    if (isValidCol(c, nc)) {
                        visitedCellsV.push_back({r, c});
                        ++nWrittenCells;
                    }
                    ++c;
                }
            }

            // Fill right column of spiral from top to bottom
            r = topRow + 1;
            c = rightCol;
            if (isValidCol(c, nc)) {
                while ((nWrittenCells < nCells) && (r <= bottomRow)) {
                    if (isValidRow(r, nr)) {
                        visitedCellsV.push_back({r, c});
                        ++nWrittenCells;
                    }
                    ++r;
                }
            }
            
            // Fill bottom row of spiral from right to left
            r = bottomRow;
            c = rightCol - 1;
            if (isValidRow(r, nr)) {
                while ((nWrittenCells < nCells) && (c >= leftCol)) {
                    if (isValidCol(c, nc)) {
                        visitedCellsV.push_back({r, c});
                        ++nWrittenCells;
                    }
                    --c;
                }
            }

            // Fill left column of spiral from bottom to left
            r = bottomRow - 1;
            c = leftCol;
            if (isValidCol(c, nc)) {
                while ((nWrittenCells < nCells) && (r > topRow - 1)) {
                    if (isValidRow(r, nr)) {
                        visitedCellsV.push_back({r, c});
                        ++nWrittenCells;
                    }
                    --r;
                }
            }
            
            // Adjust the boundary of spiral matrix for the next iteration
            --topRow;
            ++bottomRow;
            --leftCol;
            ++rightCol;
        }

        return visitedCellsV;
    }
    
private:
    
    inline bool
    isValidRow(int r, int nr) {
        return (r >= 0) && (r < nr);
    }
    
    inline bool
    isValidCol(int c, int nc) {
        return (c >= 0) && (c < nc);
    }
};
