// n => Num binary tree nodes
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
    TreeNode*
    correctBinaryTree(TreeNode* root) {
        if (!root) {
            return root;
        }
        
        // Do a reverse postorder DFS of the tree. Each time a node
        // is visited, the node value is stored in a hash table
        
        // However, when a reverse postorder is going to be done
        // on a nodes' right child, check if the right child was
        // already visited earlier and is in hash table. If yes,
        // current node is the invalid node
        correctBinaryTreeDfs(root, nullptr);
        return root;
    }
    
private:
    
    void
    postOrderDelete(TreeNode* currNode) {

        if (!currNode) {
            return;
        }
        postOrderDelete(currNode->left);
        postOrderDelete(currNode->right);
        
        delete currNode;   
    }
    
    bool
    correctBinaryTreeDfs(TreeNode * currNode,
                         TreeNode * currNodeParent) {
        
        // Visit right subtree
        if (currNode->right) {
            // Since the right child of invalid node points to another
            // node at same level to its right, check if the right
            // child was visited earlier. If yes, current node is an
            // invalid node
            if (_seenNodes.find(currNode->right->val) != _seenNodes.end()) {
                // Current node is an invalid node
                
                // Mark current nodes' parent as pointing to empty
                // subtree (i.e. delete the subtree based at current node)
                if (currNodeParent->left == currNode) {
                    currNodeParent->left = nullptr;
                } else {
                    currNodeParent->right = nullptr;
                }
                
                // Post order delete of left subtree rooted at invalid node
                // followed by invalid node deletion
                postOrderDelete(currNode->left);
                delete currNode;
                
                return true;
            }
            
            if (correctBinaryTreeDfs(currNode->right, currNode)) {
                return true;
            }
        }
        
        // Visit left subtree
        if (currNode->left) {
            if (correctBinaryTreeDfs(currNode->left, currNode)) {
                return true;
            }
        }
        
        // Visit the current node
        _seenNodes.insert(currNode->val);
        
        return false;
    }
    
    // Hash table of node values which have been already visited uptill now
    set<int> _seenNodes;
};
