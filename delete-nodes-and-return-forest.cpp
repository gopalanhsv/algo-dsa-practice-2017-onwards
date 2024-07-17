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
    vector<TreeNode*>
    delNodes(TreeNode* root, vector<int>& to_delete) {
        // Base case of null tree
        if (!root) {
            return _forestsV;
        }
        
        // Iterate over all vals which are to be deleted and store
        // in hash table so that vals can be quickly accessed
        for (auto & e : to_delete) {
            _nodeValsToBeDeleted.insert(e);
        }
        
        // Traverse the tree nodes in post order. For every node which is deleted,
        // store its (if undeleted) left subtree and (if undeleted) right subtree
        // as root of remaining forest of trees
        root = deleteNodesInPostOrder(root);
        if (root) {
            _forestsV.emplace_back(root);
        }
        
        return _forestsV;
    }
    
private:
    
    TreeNode*
    deleteNodesInPostOrder(TreeNode *currNode) {
        
        // Check the left subtree and delete the nodes matching
        // specified values there
        if (currNode->left) {
            
            TreeNode* nl = deleteNodesInPostOrder(currNode->left);
            if (!nl) {
                delete currNode->left;
                currNode->left = nullptr;
            }
        }
        
        // Check the right subtree and delete the nodes matching
        // specified values there
        if (currNode->right) {
            TreeNode* nr = deleteNodesInPostOrder(currNode->right);
            if (!nr) {
                delete currNode->right;
                currNode->right = nullptr;
            }
        }
        
        // Delete the current node if its present in hash table
        if (_nodeValsToBeDeleted.find(currNode->val) !=
            _nodeValsToBeDeleted.end()) {
            // Current node is slated for deletion. Delete the node and store the
            // resulting forest(s) subtrees if any
            // Forest rooted at left child of current node
            if (currNode->left) {
                _forestsV.emplace_back(currNode->left);
            }
            // Forest rooted at right child of current node
            if (currNode->right) {
                _forestsV.emplace_back(currNode->right);
            }
                 
            // Delete current node (delete messes up with leetcode, So 
            // just return null to mark current node deletion)
            //delete currNode;
            currNode = nullptr;
        }
        
        return currNode;
        
    }
    
    // Data members
    
    // Hash table of node values to be deleted
    unordered_set<int> _nodeValsToBeDeleted;
    
    // Vector of forest after deletion of nodes
    vector<TreeNode*> _forestsV;
};
