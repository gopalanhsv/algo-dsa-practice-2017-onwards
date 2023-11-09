// n => corrdinates.size()
// Time complexity : O(kn)
// Space complexity : O(n)

class Solution {
public:
    int
    countPairs(vector<vector<int>>& coordinates, int k) {
        // Distance between 2 points (x1, y1) & (x2, y2) should be 'k'
        // i.e. d(x1, y1, x2, y2) = (x1 ^ x2) + (y1 ^ y2) = k
        
        // => X + Y = k, where X = x1 ^ x2 & Y = y1 ^ y2
        // => Y = k - X, where X = x1 ^ x2 & Y = y1 ^ y2
        // => Y = k - X, where X ^ x2 = x1 & Y ^ y2 = y1
        // => x1 = x2 ^ X & y1 = y2 ^ (k - X) 
        
        // Since all co-ords (x, y) are g.e 0, XOR of the x/y constituents
        // of any pair of co-ordinates will be 0/+ve too. 
        // So X & Y are >= 0 & X + Y = k
        
        // Iterate over the co-ord array from L->R.
        // Hash table for storing co-ords seen so far and their occurence count
        unordered_map<int, unordered_map<int, int> > xyToCntTbl;
        int nPairs = 0;
        // First co-ord cannot form a pair with any earlier co-ord
        auto & firstCoord = coordinates[0];
        xyToCntTbl[firstCoord[0]][firstCoord[1]] = 1;
        
        for (auto j = 1; j < coordinates.size(); ++j) {
            // Current co-ordinate
            auto & xj = coordinates[j][0];
            auto & yj = coordinates[j][1];
            
            // Current co-ordinate can pair with any of the earlier seen co-odinates
            // (xi, yi) where  xi = xj ^ X & yi = yj ^ (k - X) 
            // Since X & (k - X) both have to be g.e 0, iterate over all 
            // candidate values of X & (k - X)
            for (int X = 0; X <= k; ++X) {
                // Compute candidate (xi, yi) for current X, Y (i.e. k - X)
                auto xi = xj ^ X;
                auto yi = yj ^ (k - X);
                // Check if (xi, yi) seen earlier
                auto xIter = xyToCntTbl.find(xi);
                if (xIter != xyToCntTbl.end()) {
                    auto & y2CntTbl = xIter->second;
                    auto yIter = y2CntTbl.find(yi);
                    if (yIter != y2CntTbl.end()) {
                        // Current co-ord (xj, yj) pairs with earlier seen (xi, yi)
                        nPairs += yIter->second;
                    }
                }
            }
                
            // Store current co-ord in hash table/update its occurence cnt
            xyToCntTbl[xj][yj] += 1;
        }
        
        return nPairs;
    }
};
