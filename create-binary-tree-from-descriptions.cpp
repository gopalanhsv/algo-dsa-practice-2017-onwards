// Time complexity : O(num nodes)
// Space complexity : O(num nodes)

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
    createBinaryTree(vector<vector<int>>& descriptions) {
        if (descriptions.empty()) {
            // Base case of empty tree
            return nullptr;
        }
        
        // Hash table maintaining a mapping of node values from
        // description to the respective TreeNode pointers
        unordered_map<int, TreeNode*> valToNodeTbl;
        // Hash table indicating whether a node with given value
        // is a root node or not
        // Root node will be the node which is seen in the descriptions as
        // as parent only; and not as a node/child
        unordered_map<int, bool> isRootTbl;
        
        // Iterate over each of the node descriptions
        for (auto & nodeDesc : descriptions) {
        
            auto & parentId = nodeDesc[0];
            auto & nodeId = nodeDesc[1];
            auto & nodeIsLeftChild = nodeDesc[2];
            
            // Create/get handle to the nodes (from hash table if they have been
            // already created earliers) as specified in the descriptions
            TreeNode* nodeP = getNodeHandle(nodeId, valToNodeTbl);
            TreeNode* parentP = getNodeHandle(parentId, valToNodeTbl);
            if (1 == nodeIsLeftChild) {
                // nodeP is left child of parentP node
                // Update the parent node's left child
                parentP->left = nodeP;
            } else {
                // nodeP is right child of parentP node
                // Update the parent node's right child
                parentP->right = nodeP;
            }
            
            // Current node has a parent, so it cannot be a root
            isRootTbl[nodeId] = false;
            // Current node parent is a possible root candidate
            if (isRootTbl.find(parentId) == isRootTbl.end()) {
                // Current nodes' parent was not seen earlier
                // => it is potential root candidate
                isRootTbl[parentId] = true;
            }
        }
        
        // Iterate over all nodes in the table indicating whether node
        // is a root or not
        TreeNode *rootP;
        for (auto & ent : isRootTbl) {
            if (ent.second) {
                // Current node is a root
                rootP = getNodeHandle(ent.first, valToNodeTbl);
                // Single root
                break;
            }
        }
        
        return rootP;
    }
    
private:
    
    inline TreeNode*
    getNodeHandle(int nodeId, unordered_map<int, TreeNode*>& valToNodeTbl) {
        // Lookup and return the pointer to node with given id if already
        // seen/created earlier from the hash table
        // If not seen/created earlier, create a treenode with the appropriate
        // value and add it to the hash table
        TreeNode* nodeP;
        auto iter = valToNodeTbl.find(nodeId);
        if (iter == valToNodeTbl.end()) {
            nodeP = new TreeNode(nodeId);
            valToNodeTbl[nodeId] = nodeP;
        } else {
            nodeP = iter->second;
        }
        return nodeP;
    }
};
