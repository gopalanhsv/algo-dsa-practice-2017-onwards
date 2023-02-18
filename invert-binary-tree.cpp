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
    invertTree(TreeNode* root) {
        // Null tree
        if (!root) {
            return root;
        }
        
        //invertTreeDfs(root);
        invertTreeBfs(root);
        return root;
    }
    
private:
    
    void
    invertTreeDfs(TreeNode* currNode) {
        
        // Swap the left and right subtrees rooted at current node
        swap(currNode->left, currNode->right);
        
        // Invert the subtree located at left child of current node
        if (currNode->left) {
            invertTreeDfs(currNode->left);
        }
        
        // Invert the subtree located at right child of current node
        if (currNode->right) {
            invertTreeDfs(currNode->right);
        }
    }
    
    void
    invertTreeBfs(TreeNode *root) {
        // Key idea is to visit each node level by level, and swap its left
        // and right child subtrees
        queue<TreeNode*> bfsQ;
        typedef queue<TreeNode*>::size_type qSzT;
        // Commence BFS by adding root to BFSQ
        bfsQ.push(root);
        while (!bfsQ.empty()) {
            // Visit all nodes at current level, add their children to
            // queue and swap their left and right child subtrees
            qSzT qSz = bfsQ.size();
            for (qSzT i = 0; i != qSz; ++i) {
                // Visit and dequeue vertex at Q front
                auto & tn = bfsQ.front();
                // Enqueue children of visited node to Q
                if (tn->left) {
                    bfsQ.push(tn->left);
                }
                if (tn->right) {
                    bfsQ.push(tn->right);
                }
                // Swap left and right child subtree of visited node
                swap(tn->left, tn->right);
                bfsQ.pop();
            }
        }
    }
};
