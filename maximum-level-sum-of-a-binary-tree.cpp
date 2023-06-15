// Time complexity : O(num tree nodes) / O(n)
// Space complexity : O(num tree nodes) / O(n)

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
    maxLevelSum(TreeNode* root) {
    
        if (!root) {
            // Null tree
            return 0;
        }
        
        // Exec BFS to compute the sum at each level; and track
        // the smallest level with maximum sum
        int levelWithMaxSum = 1;
        int maxLevelSumSeen = numeric_limits<int>::min();
        
        queue<TreeNode*> bfsQ;
        typedef queue<TreeNode*>::size_type qSzT;
        
        // Commence BFS
        bfsQ.push(root);
        int currLevel = 1;
        while (!bfsQ.empty()) {
            
            // Visit all nodes at current level and accumulate them
            int currLvlSum = 0;
            qSzT currLvlSz = bfsQ.size();
            for (qSzT i = 0; i < currLvlSz; ++i) {
                // Dequeue the node at front of BFS Q
                auto tn = bfsQ.front();
                bfsQ.pop();
                
                // Add the dequeued node val to level sum
                currLvlSum += tn->val;
                
                // Setup the children of dequeued node for BFS in next iteration
                if (tn->left) {
                    bfsQ.push(tn->left);
                }
                if (tn->right) {
                    bfsQ.push(tn->right);
                }
            }
            
            if (currLvlSum > maxLevelSumSeen) {
                // Update level with max sum seen so far
                maxLevelSumSeen = currLvlSum;
                levelWithMaxSum = currLevel;
            }
            
            // Next level
            currLevel++;
        }
        
        return levelWithMaxSum;
    }
};
