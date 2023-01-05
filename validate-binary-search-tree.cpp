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
    isValidBST(TreeNode* root) {
        // Perform an inorder traversal of the tree. Each node encountered
        // during the traversal must be greater than its predecessor node
        // to maintain BST property
        if (!root) {
            return true;
        }
#if 0
        TreeNode *prevNode = nullptr;
        return validBSTInorderRec(root, prevNode);
#else   
        return isValidBSTInorderIterative(root);
#endif
    }
    
private:
    
    bool
    validBSTInorderRec(TreeNode* currNode, TreeNode* &inOutPrevNode) {
        
        if (!currNode) {
            return true;
        }
        
        // Visit left subtree of current node
        if (!validBSTInorderRec(currNode->left, inOutPrevNode)) {
            return false;
        }
        
        // Visit current node
        if ((inOutPrevNode) &&
            (currNode->val <= inOutPrevNode->val)) {
            // current node fails valid BST property of being
            // greater than its predecessor
            return false;
        }
        inOutPrevNode = currNode;

        // Visit right subtree of current node
        return validBSTInorderRec(currNode->right, inOutPrevNode);
    }
    
    bool
    isValidBSTInorderIterative(TreeNode* root) {
        stack<TreeNode*> inorderStk;
        auto tNode = root;
        TreeNode *prevNode = nullptr;
        while (!inorderStk.empty() || (nullptr != tNode)) {
            if (tNode) {
                // Go down the left subtree
                inorderStk.push(tNode);
                tNode = tNode->left;
            } else {
                // Visit current node and ensure that it
                // exceeds predecessor node value
                auto currNode = inorderStk.top();
                inorderStk.pop();
                if (prevNode &&
                    currNode->val <= prevNode->val) {
                    // Current node breaks BST property
                    return false;
                }
                // Update the predecessor value
                prevNode = currNode;
                // Move on to visit right subtree
                tNode = currNode->right;
            }
        }
        
        return true;
    }
};
