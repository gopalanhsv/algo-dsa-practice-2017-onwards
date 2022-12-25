class Solution {
public:
    int
    connectSticks(vector<int>& sticks) {
        // Follow the greedy approach of always selecting the
        // two sticks of minimum cost at each step while connecting
        // the various sticks together to form a single long stick&)
        // This technique reduces the cost of connecting sticks for
        // each local decision; and leads to an over reduced global
        // minimum cost
        
        // Easily accomplished using a minHeap
        priority_queue<int, vector<int>, greater<int> > minHeap;
        // Add all sticks to PQ
        for (auto & stick : sticks) {
            minHeap.push(stick);
        }
        
        int connectingCost = 0;
        // Keep connecting sticks together till there is only
        // a single stick left
        while (minHeap.size() > 1) {
            // Get the 2 shortest sticks
            int stick1 = minHeap.top();
            minHeap.pop();
            int stick2 = minHeap.top();
            minHeap.pop();
            // Connectem them and add them back to heap. Update
            // connecting cost
            connectingCost += stick1 + stick2;
            minHeap.push(stick1 + stick2);
        }
        
        return connectingCost;
    }
};
