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
    bool
    isSameTree(TreeNode* p, TreeNode* q) {
        // Reached leaf or null subtree for both trees
        if (!p && !q) {
            return true;
        }
        
        // Check for identical current nodes p & q
        if ((p && !q) || (!p && q) || (p->val != q->val)) {
            return false;
        }
        
        // Check for identical left subtrees
        if (!isSameTree(p->left, q->left)) {
            return false;
        }
        
        // Check for identical right subtrees
        if (!isSameTree(p->right, q->right)) {
            return false;
        }
        
        return true;
    }
};
