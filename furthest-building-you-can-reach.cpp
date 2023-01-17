class Solution {
public:
    int
    furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        
        // Adopt greedy approach by starting from building 0, attempt
        // to jump as many buildings as possible and reach the rightmost
        // possible building, by reserving ladders for largest jumps
        // and bricks for the other jumps. Ladders are preferred for biggest
        // jumps as each ladder can be used to jump to infinity
        
        // The largest jumps seen so far are done by ladders. This is easily
        // tracked by using a minheap to store only the largest size jumps
        // seen so far; and restricting the heap size to the number
        // of ladders available. Whenever a new jump is encountered exceeding
        // the minimum size jump stored in min heap(ladder jumps); the new
        // jump is adjusted to be done by ladders; and minimum size jump
        // amongst the earlier ladder jumps is scheduled via bricks
        int nBuildings = heights.size();
        priority_queue<int, vector<int>, greater<int> > minHeap;
        // Iterate over the building heights sequentially from L to R
        for (int bId = 0; bId < nBuildings - 1 ; ++bId) {
            // Jump height to next building
            int climb = heights[bId + 1] - heights[bId];
            
            // Directly exec the jump if next building at same/lesser
            // height compared to current
            if (climb <= 0) {
                continue;
            }
            
            // Schedule the current jump/climb to be done via ladders first
            minHeap.push(climb);
            
            if (minHeap.size() > ladders) {
                
                // Number of jumps done so far exceeds the number of 
                // available ladders. Ladders should be used only for maximum
                // sized jumps, rest should be attempted via bricks
                
                // Move the smallest amongst the jumps earlier scheduled
                // by ladders to be done by bricks
                bricks -= minHeap.top();
                minHeap.pop();
            }
            
            // First all ladders are used for largest jumps seen so far; and
            // remainder are accomodated via bricks. Check if total of jumps
            // which can be done via bricks exceeds the number of bricks.
            // If yes, all ladders and bricks are used up and we cannot
            // proceed beyond current building
            if (bricks < 0) {
                return bId;
            }
        }
        
        // All buildings could be visited
        return nBuildings - 1;
    }
};
