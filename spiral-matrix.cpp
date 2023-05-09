// nr, nc = num matrix rows and cols respectively
// Time complexity : O(nr x nc)
// Space complexity : O(nr x nc)

class Solution {
public:
    vector<int>
    spiralOrder(vector<vector<int>>& matrix) {
        // Num matrix rows/cols
        int nr = matrix.size();
        int nc = matrix[0].size();

        // Boundary of the submatrix for spiral move
        // being executed at any instant
        int topRow = 0;
        int bottomRow = nr - 1;
        int leftCol = 0;
        int rightCol = nc - 1;

        // Output vector
        int matrixSz = nr * nc;
        vector<int> outV(matrixSz);
        int idx = 0;
        while (idx < matrixSz) {
            int r = topRow;
            int c = leftCol;
            // Left to right movement along top
            while ((idx < matrixSz) && (c <= rightCol)) {
                outV[idx++] = matrix[r][c];
                ++c;
            }
            // Top to bottom move along right
            c = rightCol;
            ++r;
            while ((idx < matrixSz) && (r <= bottomRow)) {
                outV[idx++] = matrix[r][c];
                ++r;
            }
            // Right to left move along bottom
            r = bottomRow;
            --c;
            while ((idx < matrixSz) && (c >= leftCol)) {
                outV[idx++] = matrix[r][c];
                --c;
            }
            // Bottom to top move along left
            c = leftCol;
            --r;
            while ((idx < matrixSz) && (r > topRow)) {
                outV[idx++] = matrix[r][c];
                --r;
            }

            // Adjust submatrix size for next spiral iteration
            ++topRow;
            --bottomRow;
            ++leftCol;
            --rightCol;
        }

        return outV;
    }
};
