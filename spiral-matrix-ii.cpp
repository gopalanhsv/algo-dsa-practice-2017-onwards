// nr => num matrix rows, nc => num maxtrix cols
// Time complexity : O(nr x nc)
// Space complexity : O(nr x nc)

class Solution {
public:
    vector<vector<int>>
    generateMatrix(int n) {
        // Output matrix
        vector<vector<int> > matrix(n, vector<int>(n));
        // Boundary of the submatrix for spiral move
        // being executed at any instant
        int topRow = 0;
        int bottomRow = n - 1;
        int leftCol = 0;
        int rightCol = n - 1;

        int maxCellVal = n * n;
        int cellVal = 1;

        while (cellVal <= maxCellVal) {
            // Fill top row of spiral from left to right
            int r = topRow;
            int c = leftCol;
            while ((cellVal <= maxCellVal) && (c <= rightCol)) {
                matrix[r][c] = cellVal++;
                ++c;
            }
            
            // Fill right col of spiral from top to bottom
            r = topRow + 1;
            c = rightCol;
            while ((cellVal <= maxCellVal) && (r <= bottomRow)) {
                matrix[r][c] = cellVal++;
                ++r;
            }

            // Fill bottom row of spiral from right to left
            r = bottomRow;
            c = rightCol - 1;
            while ((cellVal <= maxCellVal) && (c >= leftCol)) {
                matrix[r][c] = cellVal++;
                --c;
            }

            // Fill left col of spiral from bottom to top
            r = bottomRow - 1;
            c = leftCol;
            while ((cellVal <= maxCellVal) && (r > topRow)) {
                matrix[r][c] = cellVal++;
                --r;
            }

            // Adjust boundary of submatrix for next iteration
            // spiral move
            ++topRow;
            --bottomRow;
            ++leftCol;
            --rightCol;
        }

        return matrix;
    }
};
