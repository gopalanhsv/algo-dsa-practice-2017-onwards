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
    maxPathSum(TreeNode* root) {
        if (!root) {
            // Base case of empty tree
            return 0;
        }
        
        // Init max path sum
        _maxPSum = numeric_limits<int>::min();
        
        // Do a postorder traversal of the tree nodes, computing the
        // max path sum at each subtree and updating the same
        maxPathSumHelper(root);
        
        return _maxPSum;
    }
    
private:
    
    int
    maxPathSumHelper(TreeNode* currNode) {
        
        // Maximum path sum for path starting from left child
        int maxLeftChildToLeafPSum = 0;
        if (currNode->left) {
            maxLeftChildToLeafPSum = maxPathSumHelper(currNode->left);
        }
        
        // Maximum path sum for path starting from right child
        int maxRightChildToLeafPSum = 0;
        if (currNode->right) {
            maxRightChildToLeafPSum = maxPathSumHelper(currNode->right);
        }
        
        // Maximum path sum which includes the current node can
        // only be one of the following :-
        // 1. Includes only the current node
        // 2. Current node and left child maximum psum path
        // 3. Current node and right child maximum psum path
        // 4. Current node with left and right child maximum psum path
        int pSumWithBothLAndRSubtrees =
            maxLeftChildToLeafPSum + maxRightChildToLeafPSum + currNode->val;
        int pSumWithEitherLOrRSubtrees =
            max(maxLeftChildToLeafPSum, maxRightChildToLeafPSum) + currNode->val;
        int pSumWithOnlyCurrNode = currNode->val;
        
        // Compute and update the maximum path sum accounting for
        // paths in the subtree rooted at current node
        _maxPSum = 
            max(_maxPSum,
                max(pSumWithBothLAndRSubtrees, pSumWithEitherLOrRSubtrees));
        _maxPSum = 
            max(_maxPSum, pSumWithOnlyCurrNode);
        
        // Maximum path sum of path commencing from current node and moving
        // down to leaf either along the right or left subtrees or ending
        // at current node (in case both the subtrees have -ve path sum)
        int maxPathSumToLeaf =
            currNode->val + max(0, max(maxLeftChildToLeafPSum, maxRightChildToLeafPSum));
        
        return maxPathSumToLeaf;
    }
    
    // Data members
    // Tracks the maximum path sum seen so far during
    // postorder traversal of the tree 
    int _maxPSum;
    
};
