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
    void
    recoverTree(TreeNode* root) {
        _prevNode = nullptr;
        _loNode = nullptr;
        _hiNode = nullptr;
        
        // Do inorder traversal of BST (this should ideally give the values in
        // ascending order if no nodes are swapped). Find the first and last node
        // which break the ascending order sequence. These are the ones which
        // should be swapped to regain ordering
        recoverTreeDfsInorder(root);
        swap(_loNode->val, _hiNode->val);
    }
    
private:
    
    void
    recoverTreeDfsInorder(TreeNode* currNode) {
        // Visit left subtree
        if (currNode->left) {
            recoverTreeDfsInorder(currNode->left);
        }
        
        // Visit current node
        if (_prevNode) {
            if (_loNode) {
                // Update last node which has a value breaking the
                // ascending inorder traversal sequence of BST nodes
                // in forward direction - hi node
                if (currNode->val < _prevNode->val) {
                    _hiNode = currNode;
                }
            } else {
                // Find first node which has a value breaking the
                // ascending inorder traversal sequence of BST nodes
                // in forward direction - lo node
                // Find last node which has a value breaking the
                // ascending inorder traversal sequence of BST nodes
                // in forward direction - hi node
                if (currNode->val < _prevNode->val) {
                    _loNode = _prevNode;
                    _hiNode = currNode;
                }
            }
        }
        
        // Update previous visited node
        _prevNode = currNode;
        
        // Visit right subtree
        if (currNode->right) {
            recoverTreeDfsInorder(currNode->right);
        }
    }
    
    // Data members
    // Previous visited node
    TreeNode* _prevNode;
    
    // First node which has a value breaking the
    // ascending inorder traversal sequence of BST nodes
    // in forward direction - lo node
    TreeNode* _loNode;
    // Last node which has a value breaking the
    // ascending inorder traversal sequence of BST nodes
    // in forward direction - hi node
    TreeNode* _hiNode;
};
