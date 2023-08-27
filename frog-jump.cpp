// n => stones.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    bool
    canCross(vector<int>& stones) {
        // Hash table mapping stone positions to the set of incoming jumps
        // (number of jumps) leading to a particular position
        unordered_map<int, unordered_set<int> > stonePosToIncomingJumpsTbl;
        
        int lastStonePos = stones[stones.size() - 1];
        
        // Initialize
        // From first stone location, frog can make a jump of '1' unit
        // Add this destination stone position to incoming jump units mapping
        stonePosToIncomingJumpsTbl[stones[0] + 1].insert(1);
        
        // Iterate over the stone positions in sequential order
        for (auto & stonePos : stones) {
            
            // Check if the current location can be reached by the frog.
            // If yes, figure out the destination locations it can jump to
            auto tblIter = stonePosToIncomingJumpsTbl.find(stonePos);
            if (tblIter == stonePosToIncomingJumpsTbl.end()) {
                // Current location cannot be reached by frog, skip it
                continue;
            }
            
            // Current location reachable by frog
            // Determine new stone locations reachable from current location;
            // based on the incoming jumps
            auto & incomingJumpsSet = tblIter->second;
            for (auto & k : incomingJumpsSet) {
                // k => incoming jump value
                // Destination is current stone location + either k - 1/k/k + 1 units
                
                // Populate the hash table with new destination locations
                // and number of jump units to hit the respective locations
                
                // k - 1 unit jump from current location
                // Backward jumps are disallowed
                if (k - 1 >= 0) {
                    stonePosToIncomingJumpsTbl[stonePos + k - 1].insert(k - 1);
                }
                // k unit jump from current location
                stonePosToIncomingJumpsTbl[stonePos + k].insert(k);
                // k + 1 unit jump from current location
                stonePosToIncomingJumpsTbl[stonePos + k + 1].insert(k + 1);
            }
            
            if (stonePosToIncomingJumpsTbl.find(lastStonePos) !=
                stonePosToIncomingJumpsTbl.end()) {
                // Final destination hit in one of the new jumps from current location
                return true;
            }
        }
        
        // Final destination unreachable
        return false;
    }
};
