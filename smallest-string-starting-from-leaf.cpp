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
    string
    smallestFromLeaf(TreeNode* root) {
        if (!root) {
            return string();
        }
        
        // This is done by using a top down DFS to compute all leaf to root strings
        // and compare them to get the lexically smallest one.
        // Bottom to top version fails certain tests as there may be a situation
        // where at a left node 'c' with parent as 'z', one branch 'aba' and other being 'a';
        // branch 'a' gets chosen over 'aba' at that node leading to wrong string 'acz'
        // instead of 'abacz'
        string rootToLeafStr;
        smallestFromLeafDfs(root, rootToLeafStr);
        return _smallestStr;
    }
    
private:
    
    void
    smallestFromLeafDfs(TreeNode* currNode, string & currRootToLeafStr) {
        
        // Add current node char to the existing string built
        // from root to leaf
        currRootToLeafStr.push_back(char('a' + currNode->val));
        
        if (!currNode->left && !currNode->right) {
            // Reached leaf. Compute the string from leaf to root
            // by reversing
            string rootToLeafStr = currRootToLeafStr;
            reverse(rootToLeafStr.begin(), rootToLeafStr.end());
            // Update the lexicographically smallest string
            if (_smallestStr.empty()) {
                _smallestStr = rootToLeafStr;
            } else {
                _smallestStr = min(_smallestStr, rootToLeafStr);
            }
            
            // Backtrack and remove current node char added to string
            // built from root to leaf
            currRootToLeafStr.pop_back();
            return;
        }
        
        // Explore the left subtree, compute and update smallest leaf
        // to root for that branch
        if (currNode->left) {
            smallestFromLeafDfs(currNode->left, currRootToLeafStr);
        }

        // Explore the right subtree, compute and update smallest leaf
        // to root for that branch
        if (currNode->right) {
            smallestFromLeafDfs(currNode->right, currRootToLeafStr);
        }
        
        // Backtrack and remove current node char added to string
        // built from root to leaf
        currRootToLeafStr.pop_back();
    }
    
    // Data members
    string _smallestStr;
};
