class Solution {
public:
    int
    minStoneSum(vector<int>& piles, int k) {
        if (piles.empty()) {
            return 0;
        }
        
        // To have the min possible number of stones post 'k' ops;
        // adopt the greedy approach of always selecting the pile
        // with the max number of stones left during each stage of
        // the stone removal operation.
        // Move all the piles to a max heap (piles with most stones
        // will be at top)
        priority_queue<int, vector<int>, less<int> > maxHeap;
        long totalStones = 0;
        for (auto & pile : piles) {
            maxHeap.push(pile);
            totalStones += pile;
        }
        
        // Do 'k' iterations
        while ((k-- > 0)) {
            // Select pile with most stones
            auto pile = maxHeap.top();
            maxHeap.pop();
            // Remove stones from selected pile
            auto nStonesRemoved = pile / 2;
            if (0 == nStonesRemoved) {
                // No stone removed => wont be possible to remove stones
                // from current and remaining piles
                break;
            }
            totalStones -= nStonesRemoved;
            pile -= nStonesRemoved;
            // Insert modified pile back to heap
            if (pile > 0) {
                maxHeap.push(pile);
            }
        }
        
        return totalStones;
    }
};
