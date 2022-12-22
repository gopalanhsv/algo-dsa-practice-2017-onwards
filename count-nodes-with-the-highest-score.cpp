class Solution {
public:
    int
    countHighestScoreNodes(vector<int>& parents) {
        // Build tree (mapping from each node 'i' to list of
        // child nodes of 'i')
        buildTree(parents);
        
        // Compute the number of nodes present in the subtree
        // rooted at a node for each node in the tree (via DFS postorder)
        vector<int> nSubtreeNodesV(_nNodes, 0);
        numNodesViaDFS(0, nSubtreeNodesV);
        
        // Iterate over each node. Compute the score for each node
        // and determine the number of nodes with highest score
        int nNodesWithMaxScore = 0;
        long long maxScore = 0;
        for (int i = 0; i != _nNodes; ++i) {
            // Compute the score for current node 'i'
            
            // Assume node 'i' and connecting edges to its children
            // and parent to be removed. Score will the product of
            // subtrees sizes of subtrees created post node removal 
            
            // Init score to number of nodes in the subtree with
            // node 'i' parent after node 'i' removal
            long long score = nSubtreeNodesV[0] - nSubtreeNodesV[i];
            
            // Multiply score by number of nodes present in each of
            // child subtrees of node 'i'
            auto & childNodes = _childNodesV[i];
            if ((0 == i) && !childNodes.empty()) {
                // Special case for root node '0' as subtree towards
                // parent side will have no nodes and may mess up calcs
                score = 1;
            }
            for (auto cn : childNodes) {
                score *= nSubtreeNodesV[cn];
            }
            
            // Update the max score and number of nodes with max score
            if (score > maxScore) {
                maxScore = score;
                nNodesWithMaxScore = 1;
            } else if (score == maxScore) {
                ++nNodesWithMaxScore;
            }
        }
        
        return nNodesWithMaxScore;
    }
    
private:
    
    void
    buildTree(vector<int>& parents) {
        _nNodes = parents.size();
        _childNodesV.resize(_nNodes);
        // Tree - mapping from each node id to its child node ids
        // Skipped node id '0' as it is the root and its parent is -1
        for (int nodeId = 1; nodeId != parents.size(); ++nodeId) {
            auto & parent = parents[nodeId];
            _childNodesV[parent].emplace_back(nodeId);
        }
    }
    
    int
    numNodesViaDFS(int currNodeId, vector<int>& nSubtreeNodesV) {
        // Get the child nodes root at the current node subtree
        int numChildSubtreeNodes = 0;
        auto & childNodes = _childNodesV[currNodeId];
        // Detemine and add up the nodes present in each of
        // subtrees hanging off the current node children
        for (auto cn : childNodes) {
            numChildSubtreeNodes += numNodesViaDFS(cn, nSubtreeNodesV);
        }
        
        // Update the number of nodes in subtree rooted at current node
        nSubtreeNodesV[currNodeId] = numChildSubtreeNodes + 1;
        return nSubtreeNodesV[currNodeId];
    }
    
    // Data members
    // Number of tree nodes
    int _nNodes;
    // List of child nodes rooted at a node
    vector<vector<int> > _childNodesV;
};
