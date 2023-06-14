// Time complexity : O(num nodes) / O(n)
// Space complexity : O(num nodes) / O(n)

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
    getMinimumDifference(TreeNode* root) {
        if (!root) {
            return 0;
        }
        // Traverse the BST nodes via inorder traversal - all nodes appear in
        // non-decreasing sorted order. The minimum difference would be the minimum of
        // the differences computed between adjacent nodes
        int minDiff = numeric_limits<int>::max();
        TreeNode* prev = nullptr;
        stack<TreeNode*> inorderStk;
        TreeNode* curr = root;
        while (curr || !inorderStk.empty()) {
            if (curr) {
                // Subtree rooted at current node is setup for inorder traversal.
                // Push the current node onto stack (so that current node
                // and its right subtree is visited post left subtree visit);
                // and then move down its left subtree
                inorderStk.push(curr);
                // Setup left subtree for a visit in next iteration 
                curr = curr->left;
                
            } else {
                
                // Visit node at top of stack
                curr = inorderStk.top();
                inorderStk.pop();
                
                // Compute the value difference between current node and previously
                // visited node; and update the minimum differences between nodes
                if (prev) {
                    minDiff = min(minDiff, curr->val - prev->val);
                } 
                // Update the previous visited node to current
                prev = curr;
                
                // Set up the right subtree of current node for exploration
                curr = curr->right;
            }
        }
        
        return abs(minDiff);
    }
};
