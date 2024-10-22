// n => num tree nodes
// Time complexity : O(n + k + nlogk)
// Space complexity : O(n + k)
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
    long long
    kthLargestLevelSum(TreeNode* root, int k) {
        
        // Determine the level sum for each level of the tree via BFS
        // Use a priority queue to store the level sum s.t. the only
        // the 'k' largest level sums computed so far during the traversal
        // are retained in the PQ
        priority_queue<long long, vector<long long>, greater<long long> > minHeap;
        queue<TreeNode*> bfsQ;
        // Commence BFS
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
            
            // Add current level sum to PQ. Ensure that PQ holds only the 'k'
            // largest level sums seen so far
            minHeap.push(currLvlSum);
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        // Top of PQ will have the kth largest level sum
        return (minHeap.size() < k) ? - 1 : minHeap.top();
    }
};
