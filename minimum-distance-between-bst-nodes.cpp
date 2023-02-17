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
    minDiffInBST(TreeNode* root) {
        // Visiting a BST as per inorder result in
        // the nodes being visited in ascending order of their
        // values. So the min difference would be value of
        // smallest difference between a node and its predecessor
        // OR a node and its successor
        int minDiff = numeric_limits<int>::max();
        TreeNode *prev = nullptr;
        TreeNode * curr = root;
        stack<TreeNode*> inorderStk;
        while (curr || !inorderStk.empty()) {
            
            if (curr) {
                // Current subtree node scheduled for an inorder visit.
                // Add subtree root to stack (as it will be visited
                // post left subtree of current getting explored); then
                // proceed on to explore its left subtree
                inorderStk.push(curr);
                curr = curr->left;
            } else {
                // Visit node at top of stack
                curr = inorderStk.top();
                inorderStk.pop();
                
                if (prev) {
                    // Compute diff between current node and its predecessor
                    // Update minimum diff
                    minDiff = min(minDiff, curr->val - prev->val);
                }
                prev = curr;
                
                // Set up right subtree of visited node for inorder traversal
                curr = curr->right;
            }
        }
        return minDiff;
    }
};
