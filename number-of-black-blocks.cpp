// b => num black cell coordinates
// Time complexity : O(b)
// Space complexity : O(b)

class Solution {
public:
    vector<long long>
    countBlackBlocks(int m, int n, vector<vector<int>>& coordinates) {
        // Hash table tracking the number of black cells in each block
        unordered_map<int, unordered_map<int, int> > nBlackCellsPerBlockTbl;
        
        // Each 2 x 2 block within the grid is uniquely characterized
        // by the row and col id of the top left cell of the block
        // That is block(r, c) implies a 2 x 2 block consisting of 4 adjacent
        // valid grid cells (r, c), (r, c + 1), (r + 1, c), (r + 1, c + 1)
        
        // Iterate over each of the black cell co-ords
        for (auto & coord : coordinates) {
            // Row/col of cell coords
            auto & r = coord[0];
            auto & c = coord[1];
            // Current black cell @ (r, c) can be a part of at most
            // the following 4 blocks :-
            if ((r + 1 < m) && (c + 1 < n)) {
                // Block(r, c) with top left corner at (r, c)
                nBlackCellsPerBlockTbl[r][c] += 1;
            }
            if ((r - 1 >= 0) && (c + 1 < n)) {
                // Block(r - 1, c) with bottom left corner at (r, c)
                nBlackCellsPerBlockTbl[r - 1][c] += 1;
            }
            if ((r + 1 < m) && (c - 1 >= 0)) {
                // Block(r, c - 1) with top right corner at (r, c)
                nBlackCellsPerBlockTbl[r][c - 1] += 1;
            }
            if ((r - 1 >= 0) && (c - 1 >= 0)) {
                // Block(r - 1, c - 1) with bottom right corner at (r, c)
                nBlackCellsPerBlockTbl[r - 1][c - 1] += 1;
            }
        }

        // nBlocksTbl[i] is the number of blocks with exactly 'i' black cells
        vector<long long> nBlocksTbl(5, 0);
        // Tracks the count of unique blocks with black cells
        long long nBlocksWithBlackCells = 0;
        // Iterate over each of the valid blocks with black cells
        for (auto & blockEntryPerRow : nBlackCellsPerBlockTbl) {
            auto & blackCellBlocksPerRow = blockEntryPerRow.second;
            for (auto & blackCellBlockEntry : blackCellBlocksPerRow) {
                // Increment the count of unique blocks with given number of black cells
                auto & nBlackCells = blackCellBlockEntry.second;
                nBlocksTbl[nBlackCells]++;
                // Increment the count of unique blocks with black cells
                ++nBlocksWithBlackCells;
            } 
        }
        
        // Num 2 x 2 blocks submatrices in m x n grid
        long long nTotalBlocks = ((long long)(m - 1)) * (n - 1);
        // Update the count of blocks with nil black cells
        nBlocksTbl[0] = nTotalBlocks - nBlocksWithBlackCells;
        
        return nBlocksTbl;
    }
};
