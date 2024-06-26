// n => num BST tree nodes
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
    balanceBST(TreeNode* root) {
        if (!root) {
            // Empty input tree
            return nullptr;
        }
        
        // Balanced BST => depth of L & R BST subtrees at each node differs by at most 1
        // => Make the L & R BST subtrees differ in size by at most 1
        // => For each BST subtree always choose the root to have a value which
        //    is the mid value amongst the set of nodes in the respective subtree
        
        // For building the balanced BST from given BST :-
        // Arrange BST node vals in sorted form via an inorder traversal.
        // Then recursively build the balanced BST from the sorted vals
        inorder(root);
        
        return buildBalancedBST(0, _sortedValsV.size() - 1);
    }
    
private:
    
    void
    inorder(TreeNode* currNode) {
        // Visit the left subtree
        if (currNode->left) {
            inorder(currNode->left);
        }
        
        // Visit the subtree root
        _sortedValsV.emplace_back(currNode->val);
        
        // Visit the right subtree
        if (currNode->right) {
            inorder(currNode->right);
        }
    }
    
    TreeNode*
    buildBalancedBST(int lo, int hi) {
        // Build a balanced BST using all sorted
        // array values in closed range [lo, hi]
        
        if (lo == hi) {
            // Single node tree
            auto subTreeRootVal = _sortedValsV[lo];
            return new TreeNode(subTreeRootVal);
        }
        
        if (lo > hi) {
            // Null tree
            return nullptr;
        }
        
        // Tree root at array midpoint
        int mid = lo + (hi - lo) / 2;
        // Left subtree consists of array values [lo, mid - 1]
        auto lSubtree = buildBalancedBST(lo, mid - 1);
        // Left subtree consists of array values [mid + 1, hi]
        auto rSubtree = buildBalancedBST(mid + 1, hi);
        
        // Build balanced subtree with root at 'mid'
        auto subTreeRootVal = _sortedValsV[mid];
        return new TreeNode(subTreeRootVal, lSubtree, rSubtree);
    }
        
    // Data members
    // Input BST tree node values sorted in non-decreasing order
    vector<int> _sortedValsV;
};
