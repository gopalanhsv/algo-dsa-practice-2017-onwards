// BFS approach
// Time complexity : O(num tree nodes)
// Space complexity : O(num tree nodes)

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int>
    distanceK(TreeNode* root, TreeNode* target, int k) {
        if (!root || !target) {
            // Base case of null tree/target
            return {};
        }

        if (0 == k) {
            // Base case of 0 distance
            return {target->val};
        }
        
        return distanceKViaBFS(root, target, k);
    }

private:
    
    vector<int>
    distanceKViaBFS(TreeNode* root, TreeNode* target, int k) {
        // Build an adjacency list representation of the tree (in terms of
        // node values as per input constraints all node values are unique)
        buildTreeGraph(root);
        
        // Commence BFS from the 'target' value node in the tree graph
        // All nodes at distance 'k' from 'target' would be those at level 'k'
        unordered_set<int> visited;
        queue<int> bfsQ;
        typedef queue<int>::size_type qSzT;
        // Commence BFS from target node
        visited.insert(target->val);
        bfsQ.push(target->val);
        int level = 0;
        while (!bfsQ.empty()) {
            // Visit all the nodes at the current level
            qSzT currLvlSz = bfsQ.size();
            for (int i = 0; i != currLvlSz; ++i) {
                // Dequeue and visit the node at BFS Q front
                auto tnVal = bfsQ.front();
                bfsQ.pop();
                
                // Enqueue the unvisited neighbor nodes of above visited node for
                // a BFS visit in the next iteration
                auto & nbrNodesV = _treeGraph[tnVal];
                for (auto nbrNodeVal : nbrNodesV) {
                    if (visited.find(nbrNodeVal) == visited.end()) {
                        visited.insert(nbrNodeVal);
                        bfsQ.push(nbrNodeVal);
                    }
                }
            }
            
            // Increment level/distance from target
            if (++level == k) {
                // BFS Q will contain all nodes at distance 'k' from target
                break;
            }
        }
        
        // Nodes enqueued in the BFS Q at at at level 'k'
        vector<int> outV;
        while (!bfsQ.empty()) {
            outV.emplace_back(bfsQ.front());
            bfsQ.pop();
        }
        
        return outV;
    }
    
    void
    buildTreeGraphDfs(TreeNode* currNode) {
        auto & currNodeVal = currNode->val;
        // Build graph for left subtree recursively
        auto lChild = currNode->left;
        if (lChild) {
            _treeGraph[currNodeVal].emplace_back(lChild->val);
            _treeGraph[lChild->val].emplace_back(currNodeVal);
            buildTreeGraphDfs(lChild);
        }
        // Build graph for right subtree recursively
        auto rChild = currNode->right;
        if (rChild) {
            _treeGraph[currNodeVal].emplace_back(rChild->val);
            _treeGraph[rChild->val].emplace_back(currNodeVal);
            buildTreeGraphDfs(rChild);
        }
    }
    
    void
    buildTreeGraph(TreeNode* root) {
        
        // Do a DFS traversal and build a graph of tree node values
        buildTreeGraphDfs(root);
    }
    
    // Data members
    
    // Adjacency list representation of tree graph
    unordered_map<int, vector<int> > _treeGraph;
};
