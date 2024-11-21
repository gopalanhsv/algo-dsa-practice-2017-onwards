// Time Complexity : O(mn)
// Space Complexity : O(mn)

class Solution {
public:
    typedef enum {
        // Cell unoccupied and not guarded
        UNGUARDED = 0,
        // Cell unoccupied and and guarded
        GUARDED = 1,
        // Cell occupied by guard
        GUARD = 2,
        // Cell occupied by wall
        WALL = 3
    } CellStatusT;

    int
    countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        // Init a single grid with both guards and walls
        initialize(m, n, guards, walls);
        // Iterate over each grid cell
        for (auto r = 0; r < m; ++r) {
            for (auto c = 0; c < n; ++c) {
                if (CellStatusT::GUARD == _gridV[r][c]) {
                    // Guard present in current cell
                    // Mark all cells guarded by the guard present in current cell
                    markGuardedCells(r, c, m, n);
                }
            }
        }
        
        // Count the number of unoccupied and unguarded cells
        int nUnguardedCells = 0;
        for (auto r = 0; r < m; ++r) {
            for (auto c = 0; c < n; ++c) {
                if (CellStatusT::UNGUARDED == _gridV[r][c]) {
                    ++nUnguardedCells;
                }
            }
        }
        
        return nUnguardedCells;
    }
    
private:

    void
    initialize(int nr, int nc, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        // Create and initialize grid with all guards and walls
        _gridV.resize(nr);
        for (auto r = 0; r < nr; ++r) {
            _gridV[r].resize(nc, CellStatusT::UNGUARDED);
        }
        
        for (auto & guardCell : guards) {
            auto & r = guardCell[0];
            auto & c = guardCell[1];
            _gridV[r][c] = CellStatusT::GUARD;
        }
        
        for (auto & wallCell : walls) {
            auto & r = wallCell[0];
            auto & c = wallCell[1];
            _gridV[r][c] = CellStatusT::WALL;
        }
    }
    
    void
    markGuardedCells(int sr, int sc, int nr, int nc) {
        auto r = sr;
        auto c = sc;
        // Mark guarded cells to right of current cell
        ++c;
        while ((c < nc) &&
               (CellStatusT::GUARD != _gridV[r][c]) &&
               (CellStatusT::WALL != _gridV[r][c])) {
            _gridV[r][c] = CellStatusT::GUARDED;
            ++c;
        }
        // Mark guarded cells to left of current cell
        r = sr, c = sc;
        --c;
        while ((c >= 0) &&
               (CellStatusT::GUARD != _gridV[r][c]) &&
               (CellStatusT::WALL != _gridV[r][c])) {
            _gridV[r][c] = CellStatusT::GUARDED;
            --c;
        }
        // Mark guarded cells below current cell
        r = sr, c = sc;
        ++r;
        while ((r < nr) &&
               (CellStatusT::GUARD != _gridV[r][c]) &&
               (CellStatusT::WALL != _gridV[r][c])) {
            _gridV[r][c] = CellStatusT::GUARDED;
            ++r;
        }
        // Mark guarded cells above current cell
        r = sr, c = sc;
        --r;
        while ((r >= 0) &&
               (CellStatusT::GUARD != _gridV[r][c]) &&
               (CellStatusT::WALL != _gridV[r][c])) {
            _gridV[r][c] = CellStatusT::GUARDED;
            --r;
        }
    }

    // Data members
    // Grid with all guards and walls
    vector<vector<int> > _gridV;
};
