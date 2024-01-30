// n => costs.size() / num houses

// DP Bottom Up Iterative Approach
// Time complexity : O(n)
// Space complexity : O(n)

// DP Bottom Up Space Optimized Iterative Approach
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    minCost(vector<vector<int>>& costs) {
        return minCostDpSpaceOptimizedIterative(costs);
        //return minCostDpIterative(costs);
    }
    
private:
    
    int
    minCostDpSpaceOptimizedIterative(vector<vector<int>>& costs) {
        int nHouses = costs.size();
        int nColors = 3;
        
        // dpTbl[r][c] in the min cost to color all houses in range [0, r]
        // with the last house 'r' being colored with color 'c'
        // Space optimized dpTbl with row index 0 for calculations ending at even
        // numbered houses; and row index 1 for calculations ending at odd numbered houses
        vector<vector<int> > dpTbl(2, vector<int>(nColors, numeric_limits<int>::max()));

        // The 0th house (first house) can be colored with any of the three colors
        // and min cost is initialized to cost matrix        
        for (auto c = 0; c < nColors; ++c) {
            dpTbl[0][c] = costs[0][c];
        }
        
        for (auto h = 1; h < nHouses; ++h) {
            // Compute the minimum cost to color all the houses [0, h] with the 3 colors

            // Min cost to color house 'h' with color 'c' is sum of cost to color house
            // 'h' with color 'c' AND min of the costs to color houses [0, h - 1] with
            // previous house 'h - 1' being colored something other than 'c'
            int currHouseIdx = h % 2;
            int prevHouseIdx = (h - 1) % 2;
            dpTbl[currHouseIdx][0] =
                costs[h][0] + min(dpTbl[prevHouseIdx][1], dpTbl[prevHouseIdx][2]);
            dpTbl[currHouseIdx][1] =
                costs[h][1] + min(dpTbl[prevHouseIdx][0], dpTbl[prevHouseIdx][2]);
            dpTbl[currHouseIdx][2] =
                costs[h][2] + min(dpTbl[prevHouseIdx][0], dpTbl[prevHouseIdx][1]);
        }
        
        int lastHouseIdx = (nHouses - 1) % 2;
        return min(dpTbl[lastHouseIdx][0],
                   min(dpTbl[lastHouseIdx][1], dpTbl[lastHouseIdx][2]));
    }
    
    int
    minCostDpIterative(vector<vector<int>>& costs) {
        int nHouses = costs.size();
        int nColors = 3;
        // dpTbl[r][c] in the min cost to color all houses in range [0, r]
        // with the last house 'r' being colored with color 'c'
        vector<vector<int> > dpTbl(nHouses, vector<int>(nColors, numeric_limits<int>::max()));
        
        // The 0th house (first house) can be colored with any of the three colors
        // and min cost is initialized to cost matrix
        for (auto c = 0; c < nColors; ++c) {
            dpTbl[0][c] = costs[0][c];
        }
        
        // Iterate over the houses in range [1, nHouse - 1] progressively
        for (auto h = 1; h < nHouses; ++h) {
            // Compute the minimum cost to color all the houses [0, h] with the 3 colors

            // Min cost to color house 'h' with color 'c' is sum of cost to color house
            // 'h' with color 'c' AND min of the costs to color houses [0, h - 1] with
            // previous house 'h - 1' being colored something other than 'c'
            dpTbl[h][0] = costs[h][0] + min(dpTbl[h - 1][1], dpTbl[h - 1][2]);
            dpTbl[h][1] = costs[h][1] + min(dpTbl[h - 1][0], dpTbl[h - 1][2]);
            dpTbl[h][2] = costs[h][2] + min(dpTbl[h - 1][0], dpTbl[h - 1][1]);
        }

        return min(dpTbl[nHouses - 1][0],
                   min(dpTbl[nHouses - 1][1], dpTbl[nHouses - 1][2]));
    }
    
};
