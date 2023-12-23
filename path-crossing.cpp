// n => path.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    bool
    isPathCrossing(string path) {
    
        // Table mapping from a direction to appropriate coordinate
        // offsets from current location
        unordered_map<char, pair<int, int> > dirToOffsetTbl;
        dirToOffsetTbl['N'] = {0, 1};
        dirToOffsetTbl['S'] = {0, -1};
        dirToOffsetTbl['E'] = {1, 0};
        dirToOffsetTbl['W'] = {-1, 0};
    
        // Hash table tracking each visited coordinate
        unordered_set<int> visitedXY;
        
        // Lower 15 bits will have normalized X coordinate
        // Upper 15 bits will have normalized Y coordinate
        int shiftCnt = 15; 
        
        // Commence from origin (0, 0) -> normalised to (10^5, 10^5)
        // to avoid any -ve values of X/Y (max path length is 10^4 hops,
        // so max -ve coord can be (-10^4, -10^4)). Allows hashing with
        // a single number
        int X = 100000; int Y = 100000;
        visitedXY.emplace(X + (Y << shiftCnt));
        // Iterate over each direction in path sequentially
        for (auto & dir : path) {
            
            // Apply appropriate directional offsets to current location
            // coordinates to get the next location coords
            auto & offsetCoordsP = dirToOffsetTbl[dir];
            X += offsetCoordsP.first;
            Y += offsetCoordsP.second;
            
            int newXY = X + (Y << shiftCnt);
            if (visitedXY.find(newXY) != visitedXY.end()) {
                // Point was visited earlier => path crossing itself
                return true;
            }

            // Add the new location to hash table
            visitedXY.emplace(newXY);
        }
        
        return false;
    }
};
