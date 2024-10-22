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
    minimumLevel(TreeNode* root) {

        if (!root) {
            // Null tree
            return 0;
        }
        
        // Determine the level sum for each level of the tree via BFS
        // Track the smallest level with the minimum level sum
        queue<TreeNode*> bfsQ;
        long long minLevelSumSeenSoFar = numeric_limits<long long>::max();
        int levelWithMinSum = 0;
        // Commence BFS
        int currLvlId = 1;
        bfsQ.push(root);
        while (!bfsQ.empty()) {
            long long currLvlSum = 0;
            auto currLvlSz = bfsQ.size();
            // Iterate over all nodes at the current level and compute the level sum
            for (auto i = 0; i != currLvlSz; ++i) {
                // Dequeue the node at BFS Q front and add it to level sum
                auto tn = bfsQ.front();
                bfsQ.pop();

                currLvlSum += tn->val;
                // Schedule current node's children for BFS traversal in next level
                if (tn->left) {
                    bfsQ.push(tn->left);
                }
                if (tn->right) {
                    bfsQ.push(tn->right);
                }
            }
            
            // Update level with min level sum
            if (currLvlSum < minLevelSumSeenSoFar) {
                levelWithMinSum = currLvlId;
                minLevelSumSeenSoFar = currLvlSum;
            }
            
            // Increment the level for next iteration
            ++currLvlId;
        }
        
        return levelWithMinSum;
    }
};
