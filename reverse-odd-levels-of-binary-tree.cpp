// n => num tree nodes
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
    TreeNode*
    reverseOddLevels(TreeNode* root) {

        stack<int> oddLvlNodeVals;
        bool currLvlEven = true;

        queue<TreeNode*> lvlOrderQ;
        lvlOrderQ.push(root);
        while (!lvlOrderQ.empty()) {
            auto currLvlSz = lvlOrderQ.size();
            for (auto i = 0; i != currLvlSz; ++i) {
                auto currNode = lvlOrderQ.front();
                lvlOrderQ.pop();
                
                if (!currLvlEven) {
                    currNode->val = oddLvlNodeVals.top();
                    oddLvlNodeVals.pop();
                } else {
                    if (currNode->left) {
                        oddLvlNodeVals.push(currNode->left->val);
                    }
                    if (currNode->right) {
                        oddLvlNodeVals.push(currNode->right->val);
                    }
                }

                if (currNode->left) {
                    lvlOrderQ.push(currNode->left);
                }
                if (currNode->right) {
                    lvlOrderQ.push(currNode->right);
                }
            }
            
            currLvlEven = !currLvlEven;
        }
        
        return root;
    }
};
