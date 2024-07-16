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
    getDirections(TreeNode* root, int startValue, int destValue) {
        if (!root) {
            // Null tree
            return string();
        }
        
        // LCA = lowest common ancestor in the tree for nodes
        // with values of 'startValue' and 'endValue' respectively
        // Shortest path from 'startValue' to 'destValue' in the binary
        // tree will be in 2 parts :-
        // 1. Moving up the tree from 'startValue' node to LCA node
        // 2. Moving down the tree from LCA node to 'destValue' node
        
        // Find LCA node of 'startValue' and 'destValue'
        auto lca = findLCA(root, startValue, destValue);

        // Find path from lca to 'destValue' node via DFS
        string pathToDst;
        findTarget(lca, destValue, pathToDst);
        // Find path from lca to 'startValue' node via DFS
        string pathToSrc;
        findTarget(lca, startValue, pathToSrc);
        
        // Path from 'startValue' to LCA would be reverse of
        // path from LCA to  'startValue' -- so all directional
        // movement changed to 'up' for same
        auto & srcToLCAPath = pathToSrc;
        for (auto & c : srcToLCAPath) {
            c = 'U';
        }
        
        // Shortest path from start to dest value
        return srcToLCAPath + pathToDst;
    }
    
private:
    
    TreeNode*
    findLCA(TreeNode* currNode, int sval, int dval) {
        if (!currNode || currNode->val == sval || currNode->val == dval) {
            // Reached leaf or one of the start/destination nodes
            return currNode;
        }
        
        // Search for the LCA in the left and
        // right subtrees of current node
        auto left = findLCA(currNode->left, sval, dval);
        auto right = findLCA(currNode->right, sval, dval);

        if (left && right) {
            // Both the left and right subtrees of current node have the target
            // nodes with sval and dval each. So current node is the LCA
            return currNode;
        }
        
        if (!left && !right) {
            // Niether the left and right subtrees of current node have any of
            // the target nodes with sval or dval. No LCA possible at current node
            return nullptr;
        }

        // Either one of the left or right subtrees has LCA or sval or dval and
        // the other doesn't have any of the target vals/LCA required. Return the
        // target found (can be node with sval/dval or LCA node)
        return left ? left : right;
    }
    
    bool
    findTarget(TreeNode* currNode, int target, string& path) {
        if (currNode->val == target) {
            // Hit target at current node
            return true;
        }
        
        // Search for target in left subtree of current node
        if (currNode->left) {
            // Add branch direction to path
            path.push_back('L');
            if (findTarget(currNode->left, target, path)) {
                // Path found
                return true;
            }
            // Path not found. Remove branch direction from path
            path.pop_back();
        }
        
        // Search for target in right subtree of current node
        if (currNode->right) {
            // Add branch direction to path
            path.push_back('R');
            if (findTarget(currNode->right, target, path)) {
                // Path found
                return true;
            }
            // Path not found. Remove branch direction from path
            path.pop_back();
        }
        
        // Target not found in right/left subtree of current node
        return false;
    }
};
