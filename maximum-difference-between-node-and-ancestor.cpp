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
    int
    maxAncestorDiff(TreeNode* root) {
        if (!root) {
            return 0;
        }
        
        // Maximum difference between a node and an ancestor in a tree is
        // the max difference between the max valued node and min valued node 
        // along each root to leaf path. Traverse each root to leaf path via
        // DFS, tracking the max difference between the max & min valued node
        // seen so far
        
        return maxAncestorDiffDFS(root, root->val, root->val);
    }
    
private:
    
    int
    maxAncestorDiffDFS(TreeNode* currNode, int maxValSeen, int minValSeen) {
        
        // Current node will be the ancestor for its left and right subtrees on
        // root to leaf path. Update the max and min ancestor value for root
        // to leaf path to include current node
        maxValSeen = max(maxValSeen, currNode->val);
        minValSeen = min(minValSeen, currNode->val);
        // Compute the max diff between max and min valued node seen so
        // far on the root to leaf path
        int maxDiff = maxValSeen - minValSeen;
        
        if (!currNode->left && !currNode->right) {
            // Reached leaf
            return maxDiff;
        }
        
        // Update diff to include left subtree
        if (currNode->left) {
            maxDiff =
                max(maxDiff, maxAncestorDiffDFS(currNode->left, maxValSeen, minValSeen));
        }
        // Update diff to include right subtree
        if (currNode->right) {
            maxDiff =
                max(maxDiff, maxAncestorDiffDFS(currNode->right, maxValSeen, minValSeen));
        }
        
        return maxDiff;
    }
    
};
