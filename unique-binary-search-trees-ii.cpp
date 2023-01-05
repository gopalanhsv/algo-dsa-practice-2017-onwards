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
    vector<TreeNode*>
    generateTrees(int n) {
        if (0 == n) {
            vector<TreeNode*> resultV;
            resultV.push_back(nullptr);
            return resultV;
        }
        
        return generateBSTs(1, n);
    }
    
private:
    vector<TreeNode*>
    generateBSTs(int start, int end) {
        vector<TreeNode*> resultV;
        if (start > end) {
            // This has to be MANDATORILY done otherwise result will miss
            // subtrees with null subtrees dangling off the root/other nodws
            // Empty subtree/tree
            resultV.push_back(nullptr);
            return resultV;
        }

        if (start == end) {
            // Single node tree since start and end node values identical
            resultV.push_back(new TreeNode(start));
            return resultV;
        }
        
        // Generate all possible BSTs for current range of
        // node values [start, end] by sequentially selecting
        // various root values in given range
        for (int rootVal = start; rootVal <= end; ++rootVal) {
            
            // Root value selected as rootVal
            // BSTs possible with left subtrees having vals in range
            // [start, rootVal - 1] and right subtrees having vals
            // in range [rootVal + 1, end]
            
            // Generate all possible BST left subtrees for
            // current value of root [start, ..., rootVal - 1]
            vector<TreeNode*> leftSubtreesV = 
                generateBSTs(start, rootVal - 1);            
            
            // Generate all possible BST right subtrees for
            // current value of root [rootVal + 1, ..., end]
            vector<TreeNode*> rightSubtreesV =
                generateBSTs(rootVal + 1, end);
            
            // Now create all possible BSTs for the current root
            for (auto left : leftSubtreesV) {
                for (auto right : rightSubtreesV) {
                    auto bstRoot = new TreeNode(rootVal, left, right);
                    resultV.push_back(bstRoot);
                }
            }
        }
        
        return resultV;
    }
};
