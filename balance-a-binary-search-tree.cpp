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
        
        // Balanced BST => depth of L & R BST subtrees at each node differs at most by 1
        // => Make the L & R BST subtrees differ in size by at most 1
        // => For each BST subtree always choose the root to have a value which
        //    is the mid value amongst the set of nodes in the respective subtree
        
        // As per the above, for building the balanced BST from given BST, get all
        // the values in the BST in sorted form by doing an inorder traversal
        // Then recursively build the balanced BST from the sorted array vals
        inorder(root);
        
        return buildBalancedBST(0, _tnValsV.size() - 1);
    }
    
private:
    
    void
    inorder(TreeNode* currNode) {
        // Visit the left subtree
        if (currNode->left) {
            inorder(currNode->left);
        }
        
        // Visit the subtree root and add root value to array
        _tnValsV.emplace_back(currNode->val);
        
        // Visit the right subtree
        if (currNode->right) {
            inorder(currNode->right);
        }
    }
    
    TreeNode*
    buildBalancedBST(int lo, int hi) {
        // Build a balanced BST from all of the sorted
        // array values in closed range [lo, hi]
        
        if (lo == hi) {
            // Single node tree
            auto subTreeRootVal = _tnValsV[lo];
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
        auto subTreeRootVal = _tnValsV[mid];
        return new TreeNode(subTreeRootVal, lSubtree, rSubtree);
    }
        
    // Data members
    // Array of input BST tree node values in sorted non-decreasing order
    vector<int> _tnValsV;
};
