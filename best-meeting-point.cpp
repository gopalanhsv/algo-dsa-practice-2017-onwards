// nr => num rows, nc => num cols
// Time complexity : O(nr x nc)
// Space complexity : O(nr + nc)

class Solution {
public:
    int
    minTotalDistance(vector<vector<int>>& grid) {
        // Num row/cols
        auto nr = grid.size();
        auto nc = grid[0].size();
        
        if (!nr || !nc) {
            // Error
            return 0;
        }

        // The point 'x' at which total travel distance from each of the friends
        // point is minimum would be the median point of all the '1's in the grid.
        
        // The x/row coordinate of median would be determined by sorting the
        // x coords of all points in ascending order and finding their mid
        // The y/row coordinate of median would be determined by sorting the
        // y coords of all points in ascending order and finding their mid
        
        // Build vector of row co-ordinates of all cells in sorted order
        vector<int> rowCoordsV;
        for (auto r = 0; r != nr; ++r) {
            for (auto c = 0; c != nc; ++c) {
                if (grid[r][c]) {
                    rowCoordsV.emplace_back(r);
                }
            }
        }
        
        if (rowCoordsV.empty()) {
            return 0; // Errored input
        }
        
        // Build vector of col co-ordinates of all cells in sorted order
        vector<int> colCoordsV;
        for (auto c = 0; c != nc; ++c) {
            for (auto r = 0; r != nr; ++r) {
                if (grid[r][c]) {
                    colCoordsV.emplace_back(c);
                }
            }
        }
        
        //return minDistanceMedianApproach(rowCoordsV, colCoordsV);
        return minDistanceTwoPointerApproach(rowCoordsV, colCoordsV);
    }
    
private:
    
    int
    minDistanceMedianApproach(vector<int>& rowCoordsV, vector<int>& colCoordsV) {
        // Min travel distance would be the total distance from median
        auto medianRow = rowCoordsV[rowCoordsV.size() / 2];
        auto medianCol = colCoordsV[colCoordsV.size() / 2];
        
        // Minimum 1D distance (row) manhattan
        auto minDist = 0;
        for (auto r : rowCoordsV) {
            minDist += abs(r - medianRow);
        } 
        
        // Minimum 1D distance (column) manhattan
        for (auto c : colCoordsV) {
            minDist += abs(c - medianCol);
        }
        
        return minDist;
    }

    int
    minDistanceTwoPointerApproach(vector<int>& rowCoordsV, vector<int>& colCoordsV) {
        // The minimum 1D absolute travel distance to median is simply
        // the sum of distances between consecutive endpoints on the
        // coordinate line (in sorted order) from outward to inward
        // Easily computed via 2 pointer method
        int l = 0;
        int r = rowCoordsV.size() - 1;
        int minDist = 0;
        while (l < r) {
            minDist += (rowCoordsV[r--] - rowCoordsV[l++]);
        }
        
        l = 0;
        r = colCoordsV.size() - 1;
        while (l < r) {
            minDist += (colCoordsV[r--] - colCoordsV[l++]);
        }
        return minDist;
    }
};
