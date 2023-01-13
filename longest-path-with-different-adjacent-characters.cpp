class Solution {
public:
    int
    longestPath(vector<int>& parent, string s) {
        // Build the graph representing the tree
        buildTree(parent, s);
        
        // Init maximum path length to 1 (single node graph)
        _maxPathLen = 1;
        
        // Compute the longest path in the graph via DFS
        longestPathViaDfs(0, s);
        
        return _maxPathLen;
    }
    
private:
    
    void
    buildTree(vector<int>& parent, string& s) {
        int nNodes = parent.size();
        _childNodesTbl.resize(nNodes);
        // Iterate over each node in tree (skip node '0' as it is the
        // root). Build graph edges between a child node and its parent
        for (int cn = 1; cn != nNodes; ++cn) {
            auto p = parent[cn];
            _childNodesTbl[p].emplace_back(cn);
        }
    }
    
    int
    longestPathViaDfs(int currNode, string& s) {
        
        auto & childNodesV = _childNodesTbl[currNode];
        if (childNodesV.empty()) {
            // Current node is a leaf => longest path in the subtree rooted
            // at current node will have 0 length
            return 1;
        }
        
        // Tracks the length of the longest and the second longest path from
        // the current node down to the leaf nodes for the subtree rooted at
        // current node
        int longestPathLen = 0;
        int secondLongestPathLen = 0;        
        // Iterate over each child node hanging off the current node
        for (auto childNode : childNodesV) {
            // Determine the height of subtree rooted at the child node
            // and longest path within the same subtree
            auto treeHt = longestPathViaDfs(childNode, s);
            
            if (s[childNode] == s[currNode]) {
                // Skip paths with adjacent nodes having identical labels
                continue;
            }
            
            // Valid path
            if (treeHt > longestPathLen) {
                secondLongestPathLen = longestPathLen;
                longestPathLen = treeHt;
            } else if (treeHt > secondLongestPathLen) {
                secondLongestPathLen = treeHt;
            }
        }
        
        // Compute the length of longest path in the local subtree rooted
        // at current node (includes current node and the 2 longest branches
        // to the leaf)
        auto maxSubtreePathLen =  longestPathLen + secondLongestPathLen + 1;
        
        // Update the max path length for the entire tree
        _maxPathLen = max(_maxPathLen, maxSubtreePathLen);
        
        return longestPathLen + 1;
    }
    
    // Data members
    // Tracks the child nodes per node
    vector<vector<int> > _childNodesTbl;
    
    // Keeps track of the longest path len in the graph
    int _maxPathLen;
};
