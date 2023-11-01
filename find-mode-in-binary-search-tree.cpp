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
    findMode(TreeNode* root) {
        if (!root) {
            // Null tree
            return vector<int>();
        }

        init();
    
        // Exec an inorder traversal of BST => tree nodes are visited in ascending
        // order of their values => nodes with same value are visited one after other
        computeModeViaInorder(root);
        // Final updation to account for last node visited
        updateMode();
        
        return _modeV;
    }

private:
    
    void
    init() {
        _modeFreq = 0;
        //_prevNodeVal = 0;
        _prevNodeValFreq = 0;
    }
    
    void
    updateMode() {
        if (_prevNodeValFreq > _modeFreq) {
            // Mode value change with a higher frequency count
            _modeV.clear();
            _modeFreq = _prevNodeValFreq;
            _modeV.emplace_back(_prevNodeVal);
        } else if (_prevNodeValFreq == _modeFreq) {
            // New mode value with same frequency as previous
            _modeV.emplace_back(_prevNodeVal);
        }
        // Housekeeping
        _prevNodeValFreq = 0;
    }
    
    void
    computeModeViaInorder(TreeNode* currNode) {
        
        if (!currNode) {
            return;
        }
        
        // Visit left subtree
        computeModeViaInorder(currNode->left);
        
        // Visit current node and update mode stats
        if (currNode->val > _prevNodeVal) {
            // Current node val is not same as that of previous
            // => possibly of mode change
            updateMode();
        }
        // Update current running node number and its frequency cnt
        _prevNodeValFreq++, _prevNodeVal = currNode->val;
        
        // Visit right subtree
        computeModeViaInorder(currNode->right);
    }

    // Tracks frequency count of current running mode
    int _modeFreq;
    // Tracks the value of previously visited node and its frequency count
    int _prevNodeVal;
    int _prevNodeValFreq;
    vector<int> _modeV; // vector of mode vals
};
