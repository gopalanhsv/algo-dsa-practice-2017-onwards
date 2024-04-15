// n => num tree nodes, h => tree height
// Time complexity : O(n)
// Space complexity : O(h) / O(n)

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
    getLonelyNodes(TreeNode* root) {
        // Base case of null tree
        if (!root) {
            return _lonelyNodesV;
        }
        
        getLonelyNodesDFS(root);
        
        return _lonelyNodesV;
    }
    
private:
    
    void
    getLonelyNodesDFS(TreeNode* currNode) {
        
        TreeNode* lChild = currNode->left;
        TreeNode* rChild = currNode->right;
        
        if (!lChild && rChild) {
            // Right child is lonely node
            _lonelyNodesV.emplace_back(rChild->val);
        }
        
        if (lChild && !rChild) {
            // Left child is lonely node
            _lonelyNodesV.emplace_back(lChild->val);
        }
        
        // Determine count of lonely nodes in left subtree
        if (lChild) {
            getLonelyNodesDFS(lChild);
        }
        
        // Determine count of Lonely nodes in right subtree
        if (rChild) {
            getLonelyNodesDFS(rChild);
        }
        
        return;
    }
    
    // Data members
    vector<int> _lonelyNodesV;
};
