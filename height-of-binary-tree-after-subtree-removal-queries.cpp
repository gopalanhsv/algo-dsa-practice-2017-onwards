// n => num tree nodes, q => queries.size()
// Time Complexity : O(n + q)
// Space Complexity : O(n + q)

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int>
    treeQueries(TreeNode* root, vector<int>& queries) {
        if (!root) {
            // Null tree => queries fail
            return vector<int>();
        }
        
        // Since each tree node has a unique value, each node can be represented by its value.
        // Build a cache mapping each node/value to height of subtree rooted at that node via DFS
        
        // Exec a postorder DFS of the tree and precompute height of subtree rooted at each node
        subTreeHeight(root);
        
        for (auto & nodeVal : queries) {
            _queriedNodeToTreeHtTbl[nodeVal] = 0;
        }
        
        removeNodeAndComputeTreeHeightViaBFS(root);

        // Use the precomputed heights table to resolve queries
        auto nQueries = queries.size();
        vector<int> answersV(nQueries);
        for (auto i = 0; i != nQueries; ++i) {
            answersV[i] = _queriedNodeToTreeHtTbl[queries[i]];
        }
        return answersV;
    }
    
private:
    
    int
    subTreeHeight(TreeNode* currNode) {
        int lSubtreeHt = 0;
        // Compute left subtree height
        if (currNode->left) {
            lSubtreeHt = 1 + subTreeHeight(currNode->left);
        }
        // Compute right subtree height
        int rSubtreeHt = 0;
        if (currNode->right) {
            rSubtreeHt = 1 + subTreeHeight(currNode->right);
        }
        // Compute height of subtree rooted at current node and store
        int subtreeHt = max(lSubtreeHt, rSubtreeHt);
        _nodeValToHtTbl[currNode->val] = subtreeHt;
        return subtreeHt;
    }
    
    void
    removeNodeAndComputeTreeHeightViaBFS(TreeNode* root) {
        
        // Commence BFS/Level order traversal from root
        queue<TreeNode*> bfsQ;
        bfsQ.push(root);
        int subtreeDepth = 0;
        while (!bfsQ.empty()) {

            int maxHt = 0;
            int secondMaxHt = 0;
            unordered_set<int> currLvlNodes;
            // Visit all nodes at the current level/depth
            // Determine maximum and second maximum height amongst all subtrees at current
            // level. i.e. amongst all cousins
            auto currLvlSz = bfsQ.size();
            for (auto i = 0; i != currLvlSz; ++i) {
                // Dequeue the node at front of BFS Q and visit it
                auto tn = bfsQ.front();
                bfsQ.pop();
                
                currLvlNodes.insert(tn->val);
                
                // Update the max/second max height amongst all cousins at current level
                auto currNodeHt = _nodeValToHtTbl[tn->val];
                if (currNodeHt > maxHt) {
                    secondMaxHt = maxHt;
                    maxHt = currNodeHt;
                } else if (currNodeHt > secondMaxHt) {
                    secondMaxHt = currNodeHt;
                }
                
                // Schedule the child nodes for a BFS visit in next iteration
                if (tn->left) {
                    bfsQ.push(tn->left);
                }
                if (tn->right) {
                    bfsQ.push(tn->right);
                }
            }
            
            // Iterate over all nodes values seen in current level
            for (auto & nodeVal : currLvlNodes) {
                auto iter = _queriedNodeToTreeHtTbl.find(nodeVal);
                if (iter != _queriedNodeToTreeHtTbl.end()) {
                    // Current node has been queried.

                    // Compute tree height post current node removal
                    // Two scenarios possible:-
                    auto treeHt = subtreeDepth;
                    if (currLvlNodes.size() != 1) {
                        // Multiple nodes at current level
                        // Tree height post current node removal would be the max height
                        // of tree with branches through its cousins
                        if (_nodeValToHtTbl[nodeVal] == maxHt) {
                            treeHt += secondMaxHt;
                        } else {
                            treeHt += maxHt;
                        }
                    } else {
                        // Single node at current level
                        // Tree height post sole node removal would be the depth of level above
                        treeHt = subtreeDepth - 1;
                    }
                    // Update tree height post current node removal
                    iter->second = treeHt;
                }
            }
            
            // Increment subtree depth for next level iteration
            ++subtreeDepth;
        }
    }
    
    // Data members
    // Cache mapping each subtree node val to height of subtree rooted at that node
    unordered_map<int, int> _nodeValToHtTbl;
    // Cache mapping queried node vals to height of tree after queried node removal
    unordered_map<int, int> _queriedNodeToTreeHtTbl;
};
