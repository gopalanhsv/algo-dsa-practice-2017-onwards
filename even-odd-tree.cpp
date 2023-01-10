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
    isEvenOddTree(TreeNode* root) {
        if (!root) {
            // Base case of empty tree
            return true;
        }
        
        // Problem reduces to a simple level order tree traversal
        queue<TreeNode*> bfsQ;
        typedef queue<TreeNode*>::size_type qSzT;
        
        // Commence BFS from root/even level of 0
        bfsQ.push(root);
        // Tracks whether current level status as even/odd
        bool evenLevel = true;
        while (!bfsQ.empty()) {
            int prevNodeVal =
                (evenLevel ?
                 numeric_limits<int>::min() : numeric_limits<int>::max());
            
            // Iterate over every node at current level from L->R
            qSzT currLvlSz = bfsQ.size();
            for (qSzT i = 0; i != currLvlSz; ++i) {
                // Dequeue node at BFS Q front
                auto tn = bfsQ.front();
                bfsQ.pop();
                
                // Validate current node constraints
                auto currNodeVal = tn->val;
                if (evenLevel) {
                    // Even indexed level
                    // L2R node vals should be strictly increasing
                    // Node vals should be odd
                    if ((currNodeVal <= prevNodeVal) ||
                        (0 == (currNodeVal & 0x1))) {
                        return false;
                    }
                } else {
                    // Odd indexed level 
                    // L2R node vals should be strictly decreasing
                    // Node vals should be even
                    if ((currNodeVal >= prevNodeVal) ||
                        (1 == (currNodeVal & 0x1))) {
                        return false;
                    }
                }
                
                // Enqueue child nodes
                if (tn->left) {
                    bfsQ.push(tn->left);
                }
                if (tn->right) {
                    bfsQ.push(tn->right);
                }
                
                prevNodeVal = currNodeVal;
            }
            
            // Setup the even level status for next level 
            evenLevel = !evenLevel;
        }
        
        return true;
    }
};
