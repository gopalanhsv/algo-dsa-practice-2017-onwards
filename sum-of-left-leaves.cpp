// n => num tree nodes
// Time complexity : O(n)
// Space complexity : O(n)

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
    int
    sumOfLeftLeaves(TreeNode* root) {

        if (!root) {
            return 0;
        }
        
        int leftLeafSum = 0;

        // Compute sum of left leaves located in left subtree of current node
        if (root->left &&
            (!root->left->left && !root->left->right)) {
            // Current subtree root left child is a leaf
            leftLeafSum = root->left->val;
        } else {
            // Current subtree root left is not a leaf. Get the sum of left
            // leaves located in left subtree
            leftLeafSum += sumOfLeftLeaves(root->left);
        }

        
        // Compute sum of left leaves located in right subtree of current node
        leftLeafSum += sumOfLeftLeaves(root->right);
        
        return leftLeafSum;
    }
};
