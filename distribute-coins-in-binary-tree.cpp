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
    distributeCoins(TreeNode* root) {
        if (!root) {
            return 0;
        }
    
        // This problem is equivalent to balancing the number of coins
        // in each node via postorder traversal; and counting the number
        // of balancing moves required
        
        // At each subtree, if a child has no coins, we borrow one from
        // its parent (even if it not available, do the borrowing and carry
        // the deficit to parent). If a child has '-x' coins in deficit
        // (due to deficit operations/moves from the subtree hanging off the
        //  child), apply the deficit borrowing of -(x + 1) coins from
        // parent and this adds x + 1 to total moves required for
        // even coin distribution. Similarly, if a child has '+x' coins in
        // excess (due to distribution operations/moves from the subtree
        // hanging off the child), apply the excess distribution of 
        // (x + 1) coins to parent and this adds x + 1 to total moves
        // required for even coin distribution.
        
        // Do the above in postorder fashion from left and right child
        // to root. Total number of moves to balance the excess/deficit
        // would be the minimum number of moves for coin distribution
        
        return distributeCoinsDfs(root);
    }
    
private:
    
    int
    distributeCoinsDfs(TreeNode *currNode) {
    
        int nMoves = 0;
        
        if (currNode->left) {
            // Distribute coins in left subtree of current node s.t. all child subtree
            // nodes of left child have 1 coin each and the left child is left with
            // excess/deficit coins post the operation
            nMoves += distributeCoinsDfs(currNode->left);
            // Balance out the number of coins in left child to 1
            // Move excess coins from left child to current node; or borrow deficit
            // coins from current node and move them to left child
            int excessOrDeficitCoins = currNode->left->val - 1;
            nMoves += abs(excessOrDeficitCoins);
            currNode->val += excessOrDeficitCoins;
        }
        
        if (currNode->right) {
            // Distribute coins in right subtree of current node s.t. all child subtree
            // nodes of right child have 1 coin each and the right child is left with
            // excess/deficit coins post the operation
            nMoves += distributeCoinsDfs(currNode->right);
            // Balance out the number of coins in right child to 1
            // Move excess coins from right child to current node; or borrow deficit
            // coins from current node and move them to right child
            int excessOrDeficitCoins = currNode->right->val - 1;
            nMoves += abs(excessOrDeficitCoins);
            currNode->val += excessOrDeficitCoins;
        }
        
        return nMoves;
    }
};
