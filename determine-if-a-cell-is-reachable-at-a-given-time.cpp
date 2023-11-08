// Time complexity : O(1)
// Space complexity : O(1)
class Solution {
public:
    bool
    isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        // Since movement is allowed to all the 8 adjacent cells
        // from a cell on each tick/hop; min ticks/hops required to
        // reach finish point from start would be Chebyshev distance
        
        // Min time/hops to destination
        auto minTimeReqd = max(abs(fx - sx), abs(fy - sy));
        
        if (minTimeReqd > t) {
            // Time 't' is insufficent to reach (fx, fy) from (sx, sy)
            return false;
        }
        
        if (minTimeReqd == t) {
            // Time 't' is exactly enough to reach (fx, fy) from (sx, sy)
            return true;
        }
        
        // Time 't' is more than enough to reach (fx, fy) from (sx, sy)
        // This leads to certain cases
        
        // Case 1 : Start and end points are identical
        if ((sx == fx) && (sy == fy)) {
            // Start and end points are same
            // At time T = 0, we are at (sx, sy)
            // At time T = 1, we are adjacent to (sx, sy)
            // For any time T > 1, till 't - 1' we can circulate in the 8 adjacent
            // cells around (fx, fy)
            // At time T = t, we can hop back from one of the 8 adjacent cells
            // around (fx, fy) to (fx, fy)
            
            // => At time T == 1 one will be stuck in a cell adjacent to destination
            return (t != 1);
        }
        
        // Case 2 : Start and end points are not identical
        // Will always reach (fx, fy) from (sx, sy) as follows:-
        // At time T = 0, we are at (sx, sy)
        // At some time T < t, we are adjacent to (fx, fy)
        // Till time T == 't - 1' we can circulate in the 8 adjacent cells around (fx, fy) 
        // At time T = t, we can hop from one of the 8 adjacent cells
        // around (fx, fy) back to (fx, fy)
        return true;
    }
};
