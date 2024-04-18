// p => grid.size(), q => grid[0].size()
// Time complexity : O(pq)
// Space complexity : O(1)

class Solution {
public:
    int
    islandPerimeter(vector<vector<int>>& grid) {
        // Island perimeter = (num land squares * 4) - (total number of sides each land
        // square shares with another land square)
        // Top and left sides need to be checked only from 1st row and 1st column
        int nLandSqr = 0;
        int nTopAndLeftSidesShared = 0;
        auto nr = grid.size();
        auto nc = grid[0].size();
        // Iterate over each grid point
        for (auto r = 0; r != nr; ++r) {
            for (auto c = 0; c != nc; ++c) {
                if (1 == grid[r][c]) {
                    // Current grid point is a land square
                    ++nLandSqr;                    
                    // Total number of sides current square shares with another land square
                    // = 2 * (number of top + number of left sides it shares with land square
                    // to its top and left respectively)
                    if (r > 0) {
                        // Land square at top
                        nTopAndLeftSidesShared += grid[r - 1][c];
                    }
                    if (c > 0) {
                        // Land square at left
                        nTopAndLeftSidesShared += grid[r][c - 1];
                    }
                }
            }
        }

        return (4 * nLandSqr) - (2 * nTopAndLeftSidesShared);
    }
};
