// Time complexity : O(num nodes)
// Space complexity : O(num nodes)

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
    widthOfBinaryTree(TreeNode* root) {
        if (!root) {
            // Base case of null tree
            return 0;
        }

        // A prefect/complete binary tree nodes are numbered as follows
        // at each level from left to right
        // Level 0 -> 0
        // Level 1 -> 1, 2
        // Level 2 -> 3, 4, 5, 6
        // Level 3 -> 7, 8, 9, 10, 11, 12, 13, 14
        // Level 4 -> 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30
        // ... and so on
        // That is, each parent node numbered 'i' at a level 'l',
        // has 2 child nodes numbered '2i + 1', '2i + 2' at level 'l + 1'
        // Since the node numbers/indices become huge, even the LL C++ type will give
        // an overflow. To workaround this iss, at each level rebase the first non-null
        // index to 0, s.t that all node indices/numbers get rebased to the first non
        // null node number; and first non null node index is rebased to 0. The
        // aforementioned is esply true when the child node indices have to be calculated
        
        // Exec a BFS traversal. At each level find the distance between the first
        // and last non-null nodes by using their respective node numbers/indexes.
        // This would be the level width. The problem just requires the maximum
        // level width amongst all levels seen so far
        return widthOfBinaryTreeViaBFS(root);
    }
    
private:
    
    int
    widthOfBinaryTreeViaBFS(TreeNode* root) {
        // BFS queue of <Node pointer, node number (as per perfect binary tree> tuples
        queue<pair<TreeNode*, long long> > bfsQ;
        
        // Tracks the max level width seen so far
        long long maxLvlWidth = 0;
        // Commence BFS
        bfsQ.push({root, 0});
        while (!bfsQ.empty()) {
            // Visit all the node + associated node index pairs at current level
            auto currLvlSz = bfsQ.size();
            auto firstNonNullNodeIdx = -1;
            auto lastNonNullNodeIdx = -1;
            for (int i = 0; i != currLvlSz; ++i) {
                // Dequeue the node, node index pair from BFS Q front
                auto & nodeIdxPair = bfsQ.front();
                auto tn = nodeIdxPair.first;
                auto nodeIdx = nodeIdxPair.second;
                bfsQ.pop();
                
                if (-1 == firstNonNullNodeIdx) {
                    // First node at the current level
                    firstNonNullNodeIdx = nodeIdx;
                }
                // Update the last node for the current level
                lastNonNullNodeIdx = nodeIdx;

                // Current node index is rebased/baselined to that of the
                // the first non-null index
                nodeIdx -= firstNonNullNodeIdx;
                
                // Add the child nodes/rebased child node indices for BFS
                // traversal in next iteration
                if (tn->left) {
                    bfsQ.push({tn->left, 2 * nodeIdx + 1});
                }
                if (tn->right) {
                    bfsQ.push({tn->right, 2 * nodeIdx + 2});
                }
            }
            
            // Update the max level width seen so far
            auto currLvlWidth = lastNonNullNodeIdx - firstNonNullNodeIdx + 1;
            maxLvlWidth = max(maxLvlWidth, (long long)currLvlWidth);
        }
        
        return maxLvlWidth;
    }
};
