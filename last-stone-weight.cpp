// n = stones.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {
public:
    int
    lastStoneWeight(vector<int>& stones) {
        // Base case of no stones/single stone
        if (stones.empty()) {
            return 0;
        }
        if (stones.size() < 2) {
            return stones[0];
        }
    
        // Use a max heap to store the stone weights so
        // heaviest 2 stones can be easily selected,
        // smash them and put the new stone of reduced 
        // weight (if any) back to heap and continue the process
        // till heap is empty
        
        priority_queue<int, vector<int>, less<int> > maxHeap;
        // Add all stones to max heap
        for (auto & s : stones) {
            maxHeap.push(s);
        }
        
        // Keep smashing the two max weight stones together till
        // pile is empty or reduced to 1 stone
        while (maxHeap.size() > 1) {
            // take the 2 max wt stones and smash them
            auto bigWt = maxHeap.top();
            maxHeap.pop();
            auto smallWt = maxHeap.top();
            maxHeap.pop();
            
            auto wtAfterSmash = bigWt - smallWt;
            if (wtAfterSmash > 0) {
                // Add stone left post smash to pile
                maxHeap.push(wtAfterSmash);
            }
        }
        
        return (maxHeap.size() == 0) ? 0 : maxHeap.top();
    }
};
