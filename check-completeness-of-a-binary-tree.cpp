// Time complexity : O(num tree nodes)
// Space complexity: O(num tree nodes)

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
    isCompleteTree(TreeNode* root) {
        if (!root) {
            return true;
        }
        
        // Completeness of a binary tree is easily determined by
        // level order traversal/BFS from left to right
        queue<TreeNode*> bfsQ;
        typedef queue<TreeNode*>::size_type qSzT;
        
        // Add root to BFS Q and commence level order traversal
        bfsQ.push(root);
        bool prevVisitedNodeHadRightChild = true;
        
        while (!bfsQ.empty()) {

            // Number of nodes in current level
            qSzT currLvlSz = bfsQ.size();
            
            // Visit all nodes at current level
            for (int i = 0; i != currLvlSz; ++i) {
                // Dequeue the node at front of BFS Q
                auto tn = bfsQ.front();
                bfsQ.pop();
                
                // Enqueue the left child of dequeued node
                if (tn->left) {
                    if (!prevVisitedNodeHadRightChild) {
                        // Current node has a left child while previous visited
                        // node doesnt have a right child. Not a complete binary tree
                        return false;
                    }
                    bfsQ.push(tn->left);
                }
                
                // Enqueue the right child of dequeued node
                prevVisitedNodeHadRightChild = false;
                if (tn->right) {
                    if (!tn->left) {
                        // Current node has a right child without a left child
                        // Not a complete binary tree
                        return false;
                    }
                    
                    bfsQ.push(tn->right);
                    prevVisitedNodeHadRightChild = true;
                }
            }
            
        }
        
        // BFS/level order traversal completed w/o issues, Tree is a
        // complete binary tree
        return true;
    }
};
