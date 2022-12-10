class Solution {
public:
    int
    deleteTreeNodes(int nodes, vector<int>& parent, vector<int>& value) {
        
        // Build the tree
        vector<vector<int> > treeV(nodes);
        int root;
        for (int tn = 0; tn != nodes; ++tn) {
            // Parent node for 'tn'
            auto & pn = parent[tn];
            if (-1 == pn) {
                root = tn;
            } else {
                // 'tn' is a child of 'pn'
                treeV[pn].emplace_back(tn);
            }
        }
        
        // Do a postorder DFS traversal to determine sum of all nodes in
        // each subtree and remove those subtrees
        int nNodesToBeRemoved = 0;
        subtreesSumViaDfs(root, treeV, value, nNodesToBeRemoved);
        
        return nodes - nNodesToBeRemoved;
    }
    
private:

    pair<int, int>
    subtreesSumViaDfs(
        int currNode, vector<vector<int> >& treeV, vector<int>& nodeValV, int& nNodesToBeRemoved) {
        
        // Sum of all nodes in subtree rooted at current node
        int subtreeSum = nodeValV[currNode];
        // Number of nodes in subtree rooted at current node
        int nSubtreeNodes = 1;
        // Process child node subtrees
        auto & childNodesV = treeV[currNode];
        for (auto & childNode : childNodesV) {
            auto subtreeInfo =
                subtreesSumViaDfs(childNode, treeV, nodeValV, nNodesToBeRemoved);
            subtreeSum += subtreeInfo.first;
            nSubtreeNodes += subtreeInfo.second;
        }

        if (0 == subtreeSum) {
            // Current subtree adds up to 0. Remove all nodes in it
            nNodesToBeRemoved += nSubtreeNodes;
            // Reset the number of subtree nodes as they have been removed
            // (else they may get removed multiple times at some ancestor
            // having subtree sum of 0)
            nSubtreeNodes = 0;
        }
        
        return pair<int, int>(subtreeSum, nSubtreeNodes);
    }
    
    // Data members
    int _nNodesToBeRemoved;
};
