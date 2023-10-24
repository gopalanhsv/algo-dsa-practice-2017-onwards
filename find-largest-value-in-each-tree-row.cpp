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
    vector<int>
    largestValues(TreeNode* root) {
        if (!root) {
            // Null tree
            return vector<int>();
        }
        // Exec a level order/BFS traversal of the tree tracking
        // max valued node at each BFS level
        queue<TreeNode*> bfsQ;
        typedef queue<TreeNode*>::size_type qSzT;
        // Commence BFS traversal from tree root
        bfsQ.push(root);
        vector<int> outV;
        while (!bfsQ.empty()) {
            // Num nodes at current level
            qSzT currLvlSz = bfsQ.size();
            // Visit all nodes at current level
            int lvlMaxVal = numeric_limits<int>::min();
            for (qSzT i = 0; i != currLvlSz; ++i) {
                // Dequeue and visit node at Q front
                auto & tn = bfsQ.front();
                
                // Update max val
                lvlMaxVal = max(tn->val, lvlMaxVal);
                
                // Enqueue child nodes to BFS Q
                if (tn->left) {
                    bfsQ.push(tn->left);
                }
                if (tn->right) {
                    bfsQ.push(tn->right);
                }
                // Doing pop here to speed performance up (reference access)
                bfsQ.pop();
            }
            // Traversal over for current level. Append max value seen
            outV.emplace_back(lvlMaxVal);
        }
        
        return outV;
    }
};
