// n => min(num nodes in tree#1, num nodes in tree#2)
// Time Complexity : O(n)
// Space Complexity : O(n)

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
    flipEquiv(TreeNode* root1, TreeNode* root2) {
        return flipEquivalentRec(root1, root2);    
    }
    
private:
    
    bool
    flipEquivalentRec(TreeNode* subTree1, TreeNode* subTree2) {

        if ((subTree1 && !subTree2) || (!subTree1 && subTree2)) {
            // One subtree empty and other non-empty
            // => subtrees are not flip equivalent
            return false;
        }

        if (!subTree1 && !subTree2) {
            // Both the subtrees are empty => flip equivalence
            return true;
        }

        // Both subtrees are non-empty.
        // For flip equivalence, their root values should be same AND one of the
        // following must be satisfied :-
        // (1) Left/right subtree of subTree#1 is flip equivalent with the respective
        //     left/right subtree of subTree#2; OR
        // (2) Left/right subtree of subTree#1 is flip equivalent with the respective
        //     right/left subtree of subTree#2
        
        return ( (subTree1->val == subTree2->val) &&
                 (
                   ( flipEquivalentRec(subTree1->left, subTree2->left) &&
                     flipEquivalentRec(subTree1->right, subTree2->right) ) ||
                   ( flipEquivalentRec(subTree1->left, subTree2->right) &&
                     flipEquivalentRec(subTree1->right, subTree2->left) )
                 )
               );
    }
};
