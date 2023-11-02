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
    averageOfSubtree(TreeNode* root) {
        if (!root) {
            // Base case of null tree
            return 0;
        }

        // Exec a postorder traversal of the entire tree recursively, computing
        // the number of subtree nodes and sum of subtree node values at each
        // node, which in turn allows for the average of the subtree rooted at
        // a node to be computed
        _nNodes = 0;
        sumAndCountOfSubtreePostorder(root);

        return _nNodes;
    }
    
private:
    
    pair<long, int>
    sumAndCountOfSubtreePostorder(TreeNode *subTreeRoot) {
        // For the left subtree, determine the count of nodes whose
        // average is equal to average of the respective node values
        auto nLeftSubTreeNodes = 0;
        auto leftSubTreeSum = 0;
        if (subTreeRoot->left) {
            auto subTreeSumCountPair = sumAndCountOfSubtreePostorder(subTreeRoot->left);
            leftSubTreeSum += subTreeSumCountPair.first;
            nLeftSubTreeNodes += subTreeSumCountPair.second;
        }
        // For the right subtree, determine the count of nodes whose
        // average is equal to average of the respective node values
        auto nRightSubTreeNodes = 0;
        auto rightSubTreeSum = 0;
        if (subTreeRoot->right) {
            auto subTreeSumCountPair = sumAndCountOfSubtreePostorder(subTreeRoot->right);
            rightSubTreeSum += subTreeSumCountPair.first;
            nRightSubTreeNodes += subTreeSumCountPair.second;
        }

        // Determine the count of nodes and sum of values of all the nodes
        // rooted at the current subtree root
        auto nSubTreeNodes = 1 + nLeftSubTreeNodes + nRightSubTreeNodes;
        auto subTreeSum = subTreeRoot->val + leftSubTreeSum + rightSubTreeSum;
        // Average of values of subtree rooted at current subtree root
        auto subTreeAvg = subTreeSum / nSubTreeNodes;
        
        if (subTreeRoot->val == subTreeAvg) {
            // Increment count to include current subtree root
            ++_nNodes;
        }
        
        return {subTreeSum, nSubTreeNodes};
    }
    
    // Data members
    // Tracks the total count of nodes whose value equals the average of the
    // subtree values rooted at the respective nodes
    int _nNodes;
};
