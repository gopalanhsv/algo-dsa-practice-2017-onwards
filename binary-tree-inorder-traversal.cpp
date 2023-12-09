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
    vector<int>
    inorderTraversal(TreeNode* root) {
        if (!root) {
            return vector<int>();
        }
        
        vector<int> traversalV;
        //inorderRecursive(root, traversalV);
        inorderIterative(root, traversalV);
        
        return traversalV;
    }
    
private:
    void
    inorderRecursive(TreeNode *nodeBeingVisited, vector<int>& traversalV) {
        if (!nodeBeingVisited) {
            return;
        }
        
        // Visit left subtree
        inorderRecursive(nodeBeingVisited->left, traversalV);
        // Visit root
        traversalV.push_back(nodeBeingVisited->val);
        // Visit right subtree
        inorderRecursive(nodeBeingVisited->right, traversalV);
        
    }
    
    void
    inorderIterative(TreeNode *root, vector<int>& traversalV) {
        stack<TreeNode*> inorderStk;
        TreeNode* currNode = root;
        while (!inorderStk.empty() || currNode) {
            if (currNode) {
                // Keep moving down the left branch of current subtree,
                // saving the nodes on the stack at each step (for visiting later)
                // till the leaf node is reached
                inorderStk.push(currNode);
                currNode = currNode->left;
            } else {
                // Pop off and visit the node at top of the stack
                currNode = inorderStk.top();
                inorderStk.pop();
                traversalV.emplace_back(currNode->val);
                // Schedule the right subtree of the popped off node
                // for inorder visit in next iteration
                currNode = currNode->right;
            }
        }
    }
};
