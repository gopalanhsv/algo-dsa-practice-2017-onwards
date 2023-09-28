// d => dig.size(), a => srtifacts.size()
// Time complexity : O(d + a) as each artifact takes max 4 cells
// Space complexity : O(n ^ 2)
class Solution {
public:
    int
    digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {
        // isDugTbl[r][c] is 'true' if cell (r, c) is dug up and 'false' otherwise
        vector<vector<bool> > isDugTbl(n, vector<bool>(n, false));
        // Initialize the dug up status of the grid
        for (auto & dugCell : dig) {
            isDugTbl[dugCell[0]][dugCell[1]] = true;
        }
    
        auto nExtracted = 0;
        // Iterate over each artifact in the grid
        for (auto artifactBoundary : artifacts) {
            // Boundary of grid coords where artifacts are buried
            // Start row and start col
            auto & sr = artifactBoundary[0];
            auto & sc = artifactBoundary[1];
            // End row and start col
            auto & er = artifactBoundary[2];
            auto & ec = artifactBoundary[3];
            // Iterate over each cell of the artifact and check if all cells are excavated
            bool allArtifactCellsExcavated = true;
            for (auto r = sr; r <= er; ++r) {
                for (auto c = sc; c <= ec; ++c) {
                    if (!isDugTbl[r][c]) {
                        // Current artifact cannot be extracted as cell(r, c) is not dug up
                        allArtifactCellsExcavated = false;
                        break;
                    }
                }
                if (!allArtifactCellsExcavated) {
                    break;
                }
            }
        
            if (allArtifactCellsExcavated) {
                // Current artifact can be extracted as all its location cells are fully dug up
                ++nExtracted;
            }
        }
        return nExtracted;
    }
};
