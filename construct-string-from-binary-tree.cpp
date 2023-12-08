// n=> num tree nodes
// Time complexity : O(n)
// Space complexity : O(1)

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
    string
    tree2str(TreeNode* root) {
        if (!root) {
            return "";
        }
        
        // Execute pre-order traversal to build the string for
        // current subtree rooted at 'root'
        
        // Visit the current node/subtree root => convert
        // current node value to its string representation
        string subtreeStr(to_string(root->val));
        
        // Visit the left subtree. Convert the left subtree
        // into its string representation enclosed within
        // paranthesis and append it to current subtree string
        if (root->left) {
            subtreeStr += "(" + tree2str(root->left) + ")";
        } else {
            // Current node has no left subtree. If it has a right subtree,
            // add a placeholder string for empty left subtree by appending
            // an empty paranthesis enclosed string. This enables right subtree
            // to be identified w/o confusion during de-serialization
            if (root->right) {
                subtreeStr += "()";
            }
        }
        
        // Visit the right subtree. Convert the right subtree
        // into its string representation enclosed within
        // paranthesis and append it to current subtree string
        if (root->right) {
            subtreeStr += "(" + tree2str(root->right) + ")";
        }

        return subtreeStr;
    }
};
