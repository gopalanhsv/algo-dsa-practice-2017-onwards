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
    preorderTraversal(TreeNode* root) {
        vector<int> traversalV;
        
        #if 0
        preorderRecursive(root, traversalV);
        #else
        preorderIterative(root, traversalV);
        #endif
        return traversalV;
    }

private:
    void
    preorderRecursive(TreeNode *root, vector<int>& traversalV) {
        if (!root) {
            return;
        }
        
        // Visit root
        traversalV.push_back(root->val);
        // Traverse left subtree
        preorderRecursive(root->left, traversalV);
        // Traverse right subtree
        preorderRecursive(root->right, traversalV);
    }
    
    void
    preorderIterative(TreeNode *root, vector<int>& traversalV) {
        if (!root) {
            return;
        }
        
        // Commence by pushing root node onto traversal stack
        stack<TreeNode*> traversalStk;
        traversalStk.push(root);
        
        // Iterate till the traversal stack in non-empty
        while (!traversalStk.empty()) {
            // Pop off the node at top off traversal stack and visit it
            TreeNode *nodeBeingVisited = traversalStk.top();
            traversalStk.pop();

            traversalV.push_back(nodeBeingVisited->val);
            
            // Add right subtree of node being visited to traversal stack
            if (nodeBeingVisited->right) {
                traversalStk.push(nodeBeingVisited->right);
            }
            // Add left subtree of node being visited to traversal stack
            if (nodeBeingVisited->left) {
                traversalStk.push(nodeBeingVisited->left);
            }
        }
    }
};
