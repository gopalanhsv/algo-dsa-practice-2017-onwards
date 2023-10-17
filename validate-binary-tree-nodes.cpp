// DFS Approach
// Time complexity : O(n)
// Space complexity : O(n)

// BFS Approach
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    bool
    validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        // Following conditions have to be obeyed for a valid binary tree of 'n' nodes:-
        // (1) There should be a single root node. All nodes except the root have only a
        //     single parent; while the root has no parent. 
        // (2) A node cannot have more than 2 children
        // (3) There should be exactly 'n - 1' edges connecting all the 'n' nodes
        // i.e all nodes should form a single connected component without any loops/cycles
        //return validateTreeDFS(n, leftChild, rightChild);
        return validateTreeBFS(n, leftChild, rightChild);
    }
    
private:
    
    int
    computeRoot(int n, vector<int>& leftChildV, vector<int>& rightChildV) {
        vector<int> parentNodeV(n, -1);
        // Root will be the sole node with parent node id -1/no parent OR node with net outdegree 2
        
        // Set the parent nodes
        for (auto nodeId = 0; nodeId != n; ++nodeId) {
            auto & lChildId = leftChildV[nodeId];
            auto & rChildId = rightChildV[nodeId];
            if (-1 != lChildId) {
                parentNodeV[lChildId] = nodeId;
            }
            if (-1 != rChildId) {
                parentNodeV[rChildId] = nodeId;
            }
        }
        
        // Determine root
        auto rootId = -1;
        auto rootCnt = 0;
        for (auto nodeId = 0; nodeId != n; ++nodeId) {
            if (-1 == parentNodeV[nodeId]) {
                ++rootCnt;
                rootId = nodeId;
            }
        }
        
        // There should be a single root
        return (1 != rootCnt) ? -1 : rootId;
    }
    
    bool
    validateTreeDFS(int n, vector<int>& leftChildV, vector<int>& rightChildV) {
        // Following conditions have to be obeyed for a valid binary tree of 'n' nodes:-
        // (1) There should be a single root node. All nodes except the root have only a
        //     single parent; while the root has no parent. 
        // (2) A node cannot have more than 2 children
        // (3) There should be exactly 'n - 1' edges connecting all the 'n' nodes
        // i.e all nodes should form a single connected component without any loops/cycles
        
        // The above leads to
        // Find the tree root
        auto rootId = computeRoot(n, leftChildV, rightChildV);
        if (-1 == rootId) {
            // No/multiple root => invalid tree
            return false;
        }
        
        // Commence a DFS traversal from root. Every node should be visited and only
        // once (for full connectivity and cycle/multiple parent avoidance)
        unordered_set<int> visitedNodesV;
        stack<int> dfsStk;
        // Add root node to stack
        dfsStk.push(rootId);
        while (!dfsStk.empty()) {
            // Pop off the node at stack top and visit it
            auto nodeId = dfsStk.top();
            dfsStk.pop();
            if (visitedNodesV.find(nodeId) != visitedNodesV.end()) {
                // Node should node have been visited earlier
                // Multiple visits => cycle/loop
                return false;
            }
            visitedNodesV.insert(nodeId);
            
            // Schedule the child nodes of currently visited node for a DFS traversal in
            // subsequent iteration
            auto lChildId = leftChildV[nodeId];
            if (-1 != lChildId) {
                dfsStk.push(lChildId);
            }
            auto rChildId = rightChildV[nodeId];
            if (-1 != rChildId) {
                dfsStk.push(rChildId);
            }
        }
        
        // All nodes should be connected i.e. visited once
        return n == visitedNodesV.size();
    }

    bool
    validateTreeBFS(int n, vector<int>& leftChildV, vector<int>& rightChildV) {
        // Following conditions have to be obeyed for a valid binary tree of 'n' nodes:-
        // (1) There should be a single root node. All nodes except the root have only a
        //     single parent; while the root has no parent. 
        // (2) A node cannot have more than 2 children
        // (3) There should be exactly 'n - 1' edges connecting all the 'n' nodes
        // i.e all nodes should form a single connected component without any loops/cycles
        
        // The above leads to
        // Find the tree root
        auto rootId = computeRoot(n, leftChildV, rightChildV);
        if (-1 == rootId) {
            // No/multiple root => invalid tree
            return false;
        }
        
        // Commence a BFS traversal from root. Every node should be visited and only
        // once (for full connectivity and cycle/multiple parent avoidance)
        unordered_set<int> visitedNodesV;
        queue<int> bfsQ;
        // Add root node to queue
        bfsQ.push(rootId);
        while (!bfsQ.empty()) {
            // Visit all the nodes at the current level
            auto currLvlSz = bfsQ.size();
            for (auto i = 0; i != currLvlSz; ++i) {
                // Dequeue node at BFS Q front and visit it
                auto nodeId = bfsQ.front();
                bfsQ.pop();
                if (visitedNodesV.find(nodeId) != visitedNodesV.end()) {
                    // Node should node have been visited earlier
                    // Multiple visits => cycle/loop
                    return false;
                }
                visitedNodesV.insert(nodeId);
            
                // Schedule the child nodes of currently visited node for a BFS traversal in
                // subsequent iteration
                auto lChildId = leftChildV[nodeId];
                if (-1 != lChildId) {
                    bfsQ.push(lChildId);
                }
                auto rChildId = rightChildV[nodeId];
                if (-1 != rChildId) {
                    bfsQ.push(rChildId);
                }
            }
        }
        
        // All nodes should be connected i.e. visited once
        return n == visitedNodesV.size();
    }
};
