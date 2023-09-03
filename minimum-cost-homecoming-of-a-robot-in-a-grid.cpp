// nr => num rows, nc => num cols
// Time complexity : O(nr + nc)
// Space complexity : O(1)
class Solution {
public:
    int
    minCost(vector<int>& startPos, vector<int>& homePos, vector<int>& rowCosts, vector<int>& colCosts) {
        // At the minimum, the robot has to traverse each and every row and column 
        // between 'startPos' & 'homePos' at least once. The costs of moving over these
        // rows and cols put sa lower bound on the min cost of homecoming.
        // Traversing any other rows and cols other than those lying in between the
        // start and home cells adds to the traversal cost as all moving costs are +ve
        
        // So the min traversal cost would be obtained by moving over every row and
        // col between the start and home positions just once
        
        // Traverse from start row to end/home row
        auto & startRow = startPos[0];
        auto & endRow = homePos[0];
        int rowMoveCost = 0;
        if (endRow < startRow) {
            for (int r = endRow; r < startRow; ++r) {
                rowMoveCost += rowCosts[r];
            }
        } else {
            for (int r = startRow + 1; r <= endRow; ++r) {
                rowMoveCost += rowCosts[r];
            }
        }

        // Traverse from start col to end/home col
        auto & startCol = startPos[1];
        auto & endCol = homePos[1];
        int colMoveCost = 0;
        if (endCol < startCol) {
            for (int c = endCol; c < startCol; ++c) {
                colMoveCost += colCosts[c];
            }
        } else {
            for (int c = startCol + 1; c <= endCol; ++c) {
                colMoveCost += colCosts[c];
            }
        }
        
        return rowMoveCost + colMoveCost;
    }
};
