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
    double
    maximumAverageSubtree(TreeNode* root) {
        if (!root) {
            // Base case of null tree
            return 0;
        }

        // Exec a postorder traversal of the entire tree recursively, computing
        // the number of subtree nodes and sum of subtree node values at each
        // node, which in turn allows for the average of the subtree rooted at
        // a node to be computed
        _maxSubtreeAvg = 0.0;
        sumAndCountOfSubtreePostorder(root);

        return _maxSubtreeAvg;
    }

    
private:
    
    pair<long, int>
    sumAndCountOfSubtreePostorder(TreeNode *subTreeRoot) {
        // For the left subtree, determine the node count, sum of all node values
        // and the subtree averages at each of the subtrees
        auto nLeftSubTreeNodes = 0;
        auto leftSubTreeSum = 0;
        if (subTreeRoot->left) {
            auto subTreeSumCountPair = sumAndCountOfSubtreePostorder(subTreeRoot->left);
            leftSubTreeSum += subTreeSumCountPair.first;
            nLeftSubTreeNodes += subTreeSumCountPair.second;
        }
        // For the right subtree, determine the node count, sum of all node values
        // and the subtree averages at each of the subtrees
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
        // Average of values of tree rooted at current subtree root
        double currSubTreeAvg = (double)subTreeSum / nSubTreeNodes;
        // Update the max subtree average value seen so far
        _maxSubtreeAvg = max(_maxSubtreeAvg, currSubTreeAvg);
        
        return {subTreeSum, nSubTreeNodes};
    }
    
    // Data members
    // Tracks the max subtree average amongst all subtrees traversed in the tree
    double _maxSubtreeAvg;
};
