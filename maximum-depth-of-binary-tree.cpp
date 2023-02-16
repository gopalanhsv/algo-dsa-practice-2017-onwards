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
    maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

#if 1
        return maxDepthRecursive(root);
#else
        return maxDepthIterative(root);
#endif
    }

private:
    int
    maxDepthRecursive(TreeNode* cnode) {
        // Null node implies depth of 0

        if (!cnode->left && !cnode->right) {
            // Leaf node implies depth of 1
            return 1;
        }    
        
        // Determine depth of left and right subtrees
        int leftSubtreeDepth = 0;
        if (cnode->left) {
            leftSubtreeDepth = maxDepthRecursive(cnode->left);
        }
        
        int rightSubtreeDepth = 0;
        if (cnode->right) {
            rightSubtreeDepth = maxDepthRecursive(cnode->right);
        }
        
        // Depth of subtree rooted at current node would be the max depth
        // of left/right subtrees + 1 (to account from edge from current
        // node to left/right subtree)
        return max(leftSubtreeDepth, rightSubtreeDepth) + 1;
    }
    
    int
    maxDepthIterative(TreeNode *root) {
        // Execute BFS/level order traversal of the tree to get max
        // number of levels. The max level reached would be the max depth

        queue<TreeNode*> bfsQ;
        typedef queue<TreeNode*>::size_type qSzT;        
        
        bfsQ.push(root);
        int level = 0;
        
        while (!bfsQ.empty()) {
            // Increment level id
            ++level;
            
            // Visit all nodes at current depth/level and add their children
            // to BFS Q
            qSzT nLevelNodes = bfsQ.size();
            for (qSzT i = 0; i != nLevelNodes; ++i) {
                TreeNode *currNode = bfsQ.front();
                bfsQ.pop();
                
                if (currNode->left) {
                    bfsQ.push(currNode->left);
                }
                if (currNode->right) {
                    bfsQ.push(currNode->right);
                }
            }
        }
        
        return level;
        
    }
};
