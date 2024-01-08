// n => num binary tree nodes
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
    rangeSumBST(TreeNode* root, int low, int high) {
        if (!root) {
            return 0;
        }
        
        // Exec an inorder traversal of the BST visiting nodes with
        // values in teh specified range [low, high] and ignoring the rest
        return rangeSumRec(root, low, high);
    }
    
private:
    int
    rangeSumRec(TreeNode* currNode, int lo, int hi) {
        if (!currNode) {
            return 0;
        }
        
        auto currNodeSubtreeRangeSum = 0;
        auto key = currNode->val;
        
        // Current node in range => added to sum
        if (key >= lo && key <= hi) {
            currNodeSubtreeRangeSum += key;
        }
        // Inorder of left subtree nodes iff within specified range 
        if (key > lo) {
            // Visit left subtree
            currNodeSubtreeRangeSum += rangeSumRec(currNode->left, lo, hi);
        }
        // Inorder of right subtree nodes iff within specified range
        if (key < hi) {
            // Visit right subtree
            currNodeSubtreeRangeSum += rangeSumRec(currNode->right, lo, hi);
        }
        
        return currNodeSubtreeRangeSum;
    }
};
