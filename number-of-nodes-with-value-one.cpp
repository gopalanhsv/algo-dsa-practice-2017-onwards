class Solution {
public:
    int
    numberOfNodes(int n, vector<int>& queries) {
        
        // Tracks the number of updates per nodes
        vector<long> nNodeUpdatesV(n + 1, 0);
        // Order of queries/updates is immaterial -- only the
        // final steady state matters. Apply the query/update
        // to the respective nodes
        for (auto & query : queries) {
            nNodeUpdatesV[query]++;
        }
        
        int onesNodeCnt = 0;
        // The tree is organized s.t parent node indices
        // are l.t their child nodes (like a heap structure)
        // Iterate over the tree nodes from root onwards to
        // children as a level order traversal
        for (int nodeIdx = 1; nodeIdx <= n; ++nodeIdx) {
            
            auto parentNodeIdx = nodeIdx / 2;
            // Propagate the flips/updates made at current
            // node parent down the subtree to its child
            nNodeUpdatesV[nodeIdx] += nNodeUpdatesV[parentNodeIdx];
            
            // Even number of updates => node is at initial value of 0
            // Odd number of updates => node is toggled from initial value of 0
            if (1 == (nNodeUpdatesV[nodeIdx] & 0x1)) {
                // Node is toggled from initial value of 0 and is 1
                ++onesNodeCnt;
            }
        }
        
        return onesNodeCnt;
    }
};
