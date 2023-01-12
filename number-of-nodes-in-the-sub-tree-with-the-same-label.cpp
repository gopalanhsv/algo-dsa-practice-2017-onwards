class Solution {
public:
    vector<int>
    countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        // Set up the graph and internal state
        init(n, edges);
        
        // Do a DFS traversal of the tree commencing at node '0'
        // and determine the number of nodes in a subtree with same label
        // as subtree root
        vector<bool> visitedV(n, false);
        countSubtreesWithSameLabel(0, labels, visitedV);
        
        return _nSubtreeNodeCntV;
    }
    
    
private:
    
    void
    init(int n, vector<vector<int>>& edges) {
        
        _adjListTbl.resize(n);
        _labelCntPerSubtreeV.resize(n, vector<int>(26, 0));
        _nSubtreeNodeCntV.resize(n, 0);
        
        // Build the graph adjacency list by iterating over the edges
        for (auto & e : edges) {
            // Source and destination vertex
            auto & u = e[0];
            auto & v = e[1];
            _adjListTbl[u].emplace_back(v);
            _adjListTbl[v].emplace_back(u);
        }
    }
    
    void
    countSubtreesWithSameLabel(
        int currNode, string& nodeLabels, vector<bool>& visitedV) {
        
        // Mark current node as visited (to prevent back/reverse path loops)
        visitedV[currNode] = true;
        
        // Iterate over each of the subtree child nodes
        auto & childNodesV = _adjListTbl[currNode];
        for (auto & childNode : childNodesV) {
            
            // Visit the entire subtree rooted at the child node
            if (!visitedV[childNode]) {
                // Determine the count of each label in each of the
                // subtrees rooted at the child node
                countSubtreesWithSameLabel(childNode, nodeLabels, visitedV);

                // Update the count of each label in the subtree rooted
                // at current node to account for the subtree rooted at the
                // child node explored above
                for (int labelIdx = 0; labelIdx != 26; ++labelIdx) {
                    _labelCntPerSubtreeV[currNode][labelIdx] += 
                        _labelCntPerSubtreeV[childNode][labelIdx];
                }
            }
        }
        
        // Current node label; include current node in count
        auto currNodeLabel = int(nodeLabels[currNode] - 'a');
        _labelCntPerSubtreeV[currNode][currNodeLabel] += 1;
        
        // Number of subtree nodes with same label as subtree root/current node
        _nSubtreeNodeCntV[currNode] = 
            _labelCntPerSubtreeV[currNode][currNodeLabel];
    }
    
    // Data members
    // Adjacency list representation of the graph
    vector<vector<int> > _adjListTbl;
    
    // Tracks the counts of each of the labels present in every
    // subtree rooted at the subtree node.
    // _labelCntPerSubtreeV[i][c] gives the count of nodes with 
    // label 'c' (i.e. 'a' + c) in the subtree rooted at node 'i'
    vector<vector<int> > _labelCntPerSubtreeV;
    
    // Tracks the count of subtree nodes with same label as the
    // subtree root/node on a per node basis
    vector<int> _nSubtreeNodeCntV;
};
