// Time Complexity
// O(num tree nodes)
// Space Complexity
// O(tree height)

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
    sumNumbers(TreeNode* root) {
        if (!root) {
            // Null root
            return 0;
        }
        
        // Get the sum of all root to leaf numbers via iterative DFS preorder
        //return sumRootToLeafDfsPreorderIterative(root);
        
        // Get the sum of all root to leaf numbers via DFS preorder
        int sumOfAllRootToLeafNums = 0;
        int pathNodesNumber = 0;
        sumRootToLeafDfsR(root, pathNodesNumber, sumOfAllRootToLeafNums);
        return sumOfAllRootToLeafNums;
    }
    
private:
    
    void
    sumRootToLeafDfsR(TreeNode* currNode, int pathNodesNumber, 
                    int & sumOfAllRootToLeafNums) {
        
        // Update the number represented by path from root to
        // current node to include current node value
        pathNodesNumber = 10 * pathNodesNumber + currNode->val;
        
        if (!currNode->left && !currNode->right) {
            // Leaf node reached. Add root to leaf path number to total sum
            sumOfAllRootToLeafNums += pathNodesNumber;
            return;
        }
        
        // Visit the left subtree and right subtree to and sum up the root to leaf
        // numbers for each leaf node located in the respective subtrees
        if (currNode->left) {
            sumRootToLeafDfsR(currNode->left,
                             pathNodesNumber, sumOfAllRootToLeafNums);
        }
        
        if (currNode->right) {
            sumRootToLeafDfsR(currNode->right,
                             pathNodesNumber, sumOfAllRootToLeafNums);
        }
    }
    
    int
    sumRootToLeafDfsPreorderIterative(TreeNode* root) {
        // Preorder DFS stack which holds set of nodes to be visited
        // and the number consisting of digits along the path from
        // root to node  
        stack<pair<TreeNode*, int> > dfsStk;
        int sum = 0;
        // Add root to DFS stack
        dfsStk.push(pair<TreeNode*, int>(root, root->val));
        // Commence preorder dfs
        while (!dfsStk.empty()) {
            // Pop off the node at the top of DFS stack and visit it
            auto & ste = dfsStk.top(); // ste => stack entry
            // Current node
            TreeNode * cn = ste.first;
            // Number represented by digits from root to current node
            int rootToNodePathNum = ste.second;
            dfsStk.pop();
            
            if (!cn->left && !cn->right) {
                // Current node is a leaf. Update sum
                sum += rootToNodePathNum;
                continue;
            }            
            
            // Set up right subtree for preorder DFS
            if (cn->right) {
                int rootToRightChildPathNum =
                    10 * rootToNodePathNum + cn->right->val;
                //dfsStk.push(pair<TreeNode*, int>(cn->right, rootToRightChildPathNum));
                dfsStk.push({cn->right, rootToRightChildPathNum});
            }
            
            // Set up left subtree for preorder DFS
            if (cn->left) {
                int rootToleftChildPathNum =
                    10 * rootToNodePathNum + cn->left->val;
                //dfsStk.push(pair<TreeNode*, int>(cn->left, rootToleftChildPathNum));
                dfsStk.push({cn->left, rootToleftChildPathNum});
            }
        }
        
        return sum;
    }
};
