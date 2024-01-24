// n => sticks.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {
public:
    int
    connectSticks(vector<int>& sticks) {
        // Adopt the greedy approach of always selecting two sticks of minimum
        // cost at each step while connecting the various sticks together to
        // form a single long stick. This technique optimizes the cost of connecting
        // sticks for each local decision; and leads to an omptimized global minimum cost
        
        // Easily accomplished using a minHeap
        priority_queue<int, vector<int>, greater<int> > minHeap;
        // Add all sticks to PQ
        for (auto & stick : sticks) {
            minHeap.push(stick);
        }
        
        int connectingCost = 0;
        // Connect sticks together till a single stick is left
        while (minHeap.size() > 1) {
            // Get the 2 shortest sticks
            auto stick1 = minHeap.top();
            minHeap.pop();
            auto stick2 = minHeap.top();
            minHeap.pop();
            // Connect them and add new resulting stick back to heap
            // Update connecting cost
            connectingCost += stick1 + stick2;
            minHeap.push(stick1 + stick2);
        }
        
        return connectingCost;
    }
};
