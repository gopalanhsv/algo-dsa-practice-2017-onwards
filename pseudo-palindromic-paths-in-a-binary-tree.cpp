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
    pseudoPalindromicPaths(TreeNode* root) {
        if (!root) {
            // Null/empty tree
            return 0;
        }

        _nPseudoPalindromicPaths = 0;
        // Traverse over all root to leafs paths via DFS; and employ
        // backtracking to compute the number of pseudo-palindromic paths
        rootToLeafPathViaDfs(root);

        return _nPseudoPalindromicPaths;
    }
    
private:
    
    bool
    currentRootToLeafPathPseudoPalindromic() {
        // Returns true if the nodes on the current path from root to
        // leaf can be rearranged to form a palindrome, false otherwise
        
        // Possible only if all the node values have an even frequency
        // count with at most one node having an odd frequency count
        int nOddOccurences = 0;
        // Iterate over t
        for (auto & entry : _pathNodesFreqCntTbl) {
            // Frequency count of node with value 'entry.first'
            auto & fc = entry.second;
            if (1 == (fc & 0x1)) {
                // Current node has an odd frequency count
                if (++nOddOccurences > 1) {
                    // Number of nodes with odd frequency count exceeds 1
                    // => pseudo-palindromic root to leaf path impossible 
                    return false;
                }
            }
        }
        
        return true;
    }
    
    void
    rootToLeafPathViaDfs(TreeNode* currNode) {
        
        // Explore subtree root at current node
        
        // Add current node to the path running from root to leaf)
        _pathNodesFreqCntTbl[currNode->val]++;
        if (!currNode->left && !currNode->right) {
            // Current node is a leaf
            if (currentRootToLeafPathPseudoPalindromic()) {
                // Current root to leaf path is pseudo-palindromic
                ++_nPseudoPalindromicPaths;
            }
        }
        
        // Visit left subtree of current node down to leaf
        if (currNode->left) {
            rootToLeafPathViaDfs(currNode->left);
        }
        
        // Visit right subtree of current node down to leaf
        if (currNode->right) {
            rootToLeafPathViaDfs(currNode->right);
        }
        
        // Done exploring all paths passing through current node down
        // to leaf. Backtrack and remove the current node from root to leaf path
        _pathNodesFreqCntTbl[currNode->val]--;
    }
    
    // Data memnbers
    // Number of pseudo palindromic paths
    int _nPseudoPalindromicPaths;
    // Tracks node values with their respective occurrence counts on the path
    // from root to leaf for the current path being traversed during DFS
    unordered_map<int, int> _pathNodesFreqCntTbl;
    
};
