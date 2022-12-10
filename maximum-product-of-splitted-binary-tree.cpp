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
    maxProduct(TreeNode* root) {
        // Base case of null/single node tree
        if (nullptr == root || (!root->left && !root->right)) {
            return 0;
        }
        
        // Find sum all nodes in tree via DFS
        _allNodesSum = subTreeSum(root);
        
        // For each node, find the subtree sum of subtree rooted at that
        // node via postorder DFS. Multiply this subtree sum by sum of
        // remaining nodes in tree. The link betweem the subtree root 
        // and remaining tree acts as split edge. We just need to track
        // the maxValue of this product
        _maxProd = 0;
        productOfSubtreeSumWithRemainingTreeNodes(root);
        
        return _maxProd % (1000000000 + 7);
    }
    
private:
    
    int
    subTreeSum(TreeNode* root) {
        // Subtree sum of tree rooted at current node
        // Left subtree sum
        int sum = root->val;
        if (root->left) {
            sum += subTreeSum(root->left);    
        }
        
        // // Right subtree sum
        if (root->right) {
            sum += subTreeSum(root->right);    
        }
        
        return sum;
    }
    
    int
    productOfSubtreeSumWithRemainingTreeNodes(TreeNode* root) {
        
        // Left subtree sum
        int lSubTreeSum = 0;
        if (root->left) {
            lSubTreeSum =
                productOfSubtreeSumWithRemainingTreeNodes(root->left);    
        }
        
        // // Right subtree sum
        int rSubTreeSum = 0;
        if (root->right) {
            rSubTreeSum =
                productOfSubtreeSumWithRemainingTreeNodes(root->right);    
        }
        
        // Sum of subtree rooted at current node
        int sum = root->val + lSubTreeSum + rSubTreeSum;
        
        // Product between current node subtree sum and remaining tree nodes
        // i.e. split tree between subtree root and its parent
        long prod = long(sum) * (_allNodesSum - sum);
        // Track the maximum product
        _maxProd = max(prod, _maxProd);
        
        return sum;
    }
    
private:
    
    int _allNodesSum;
    long _maxProd;
};
