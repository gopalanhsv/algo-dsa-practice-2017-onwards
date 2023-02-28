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
    findDuplicateSubtrees(TreeNode* root) {
        if (!root) {
            // Empty tree
            return _duplicateSubtreeRootV;
        }
        
        findDuplicateSubtreesApproach1(root);
        
        return _duplicateSubtreeRootV;
    }
    
private:

    void
    findDuplicateSubtreesApproach1(TreeNode* root) {
        // Exec a post order DFS; and construct the serialized representation of
        // the subtree root at each of the nodes. Maintain a hash table mapping
        // the serialized representation to the count of such subtrees seen so far
        // This enables the detection of all unique duplicate subtrees
        subtreeStrViaDfs(root);
    }
    
    string
    subtreeStrViaDfs(TreeNode* currNode) {
        
        if (!currNode) {
            // Null subtree rooted at current node
            return "";
        }
        
        // Visit left subtree and get its serialized representation
        auto lSubtreeStr = subtreeStrViaDfs(currNode->left);
        // Visit right subtree and get its serialized representation
        auto rSubtreeStr = subtreeStrViaDfs(currNode->right);
        
        // Visit current node
        // Construct the serialized string representation for the
        // subtree rooted at the current node
        auto currSubtreeStr =
            "(" + lSubtreeStr + ")" +
            to_string(currNode->val) +
            "(" + rSubtreeStr + ")";
        
        // Update the count of subtrees identical to the current node subtree
        auto subtreeCnt = ++_subtreeStrToCntTbl[currSubtreeStr];
        if (subtreeCnt == 2) {
            // There is at least one subtree with identical structure to
            // current node subtree. Add the current subtree to the output
            // on the first duplicate detection; as only a single duplicate
            // instance needs to be shown
            _duplicateSubtreeRootV.emplace_back(currNode);
        }
        
        return currSubtreeStr;
    }
    
    
    // Data members
    
    // Subtrees are represented as serialized strings
    // Hash table maintaining a mapping between subtree representation
    // to the count of such subtrees seen so far
    unordered_map<string, int> _subtreeStrToCntTbl;
    // Output array of duplicate subtrees
    vector<TreeNode*> _duplicateSubtreeRootV;
};
