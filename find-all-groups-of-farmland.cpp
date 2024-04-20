// m => land.size(), n => land[0].size()
// Time complexity : O(mn)
// Space complexity : O(1)

class Solution {
public:
    vector<vector<int>>
    findFarmland(vector<vector<int>>& land) {
        
        // Init num rows/cols of land grid
        _nr = land.size();
        _nc = land[0].size();
        
        vector<vector<int> > outV;
        
        // Since each farmland group is rectangular, iterate over the land grid in row
        // major fashion examining each row in sequence from top to bottom while
        // moving from L->R in each row
        for (auto r = 0; r < _nr; ++r) {
            for (auto c = 0; c < _nc; ++c) {
                if (1 == land[r][c]) {
                    // Top-left corner of unexplored patch of group of farmlands hit
                    // Explore all the farmlands forming this group/patch and determine
                    // the lower right corner of this group. Mark all the explored
                    // farmlands in this group as forested land to avoid revisit
                    // Top left coords
                    auto tlr = r;
                    auto tlc = c;
                    // Bottom right coords
                    auto brr = r;
                    auto brc = c;
                    exploreFarmlandGroup(land, tlr, tlc, brr, brc);
                    outV.push_back({tlr, tlc, brr, brc});
                    // Update col to rightmost col of farmland group
                    c = brc;
                }
            }
        }
        
        return outV;
    }
    
private:
    
    void
    exploreFarmlandGroup(
        vector<vector<int>>& land, int startRow, int startCol, int& bottomRow, int& rightmostCol) {
        auto r = startRow;
        auto c = startCol;
        
        // Current farmland group top left is at (sr, sc)
        // Determine farmland bottom left corner by vertical down move
        while ((r < _nr) && (1 == land[r][c])) {
            // Mark leftmost col as explored/forest land
            land[r][c] = 0;
            bottomRow = r++;
        }

        // Determine farmland bottom right corner by horizontal right move
        r = bottomRow;
        ++c;
        while ((c < _nc) && (1 == land[r][c])) {
            // Mark bottom row as explored/forest land
            land[r][c] = 0;
            rightmostCol = c++;
        }
        
        // Mark all cells/land in the current farmland group as explored
        for (auto r = startRow; r <= bottomRow; ++r) {
            for (auto c = startCol + 1; c <= rightmostCol; ++c) {
                land[r][c] = 0;
            }
        }
    }
    
    // Data members
    // Num land grid row/cols
    int _nr;
    int _nc;
};
