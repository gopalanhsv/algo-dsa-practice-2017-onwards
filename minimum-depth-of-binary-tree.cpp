// DFS
// Time complexity : O(num tree nodes) / O(n)
// Space complexity : O(num tree nodes) / O(n)
// BFS
// Time complexity : O(num tree nodes) / O(n)
// Space complexity : O(num tree nodes) / O(n)

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
    minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        
        return minDepthDfs(root, 1, numeric_limits<int>::max());
        //return minDepthBfs(root);
    }
    
private:
    
    int
    minDepthDfs(TreeNode * currNode, int currNodeDepth, int minDepthSeenSoFar) {
        if (!currNode->left && !currNode->right) {
            // Current node is a leaf
            return currNodeDepth;
        }
        
        if (currNodeDepth + 1 > minDepthSeenSoFar) {
            // No need to explore this branch/subtree of tree as 
            // a leaf node already found with lesser depth
            return minDepthSeenSoFar;
        }
        
        // Check if left subtree of current node has a leaf node
        // with a lesser depth than encountered uptill now
        if (currNode->left) {
            minDepthSeenSoFar =
                min(minDepthSeenSoFar,
                    minDepthDfs(currNode->left, currNodeDepth + 1, minDepthSeenSoFar));
        }
        
        // Check if right subtree of current node has a leaf node
        // with a lesser depth than encountered uptill now
        if (currNode->right) {
            minDepthSeenSoFar =
                min(minDepthSeenSoFar,
                    minDepthDfs(currNode->right, currNodeDepth + 1, minDepthSeenSoFar));
        }
        
        return minDepthSeenSoFar;
    }
    
    int
    minDepthBfs(TreeNode *root) {
        // Commence BFS traversal from the root, increase node depth at each new level
        // The first leaf node visited will have the least depth
        queue<TreeNode*> bfsQ;
        typedef queue<TreeNode*>::size_type qSzT;
        bfsQ.push(root);
        int depth = 1;
        while (!bfsQ.empty()) {
            // Visit all nodes at current level and stop at first leaf
            qSzT qSz = bfsQ.size();
            for (qSzT i = 0; i != qSz; ++i) {
                // Dequeue node at Q front and add its children to BFS Q
                auto tn = bfsQ.front();
                bfsQ.pop();
                
                if (!tn->left && !tn->right) {
                    // Hit a leaf node
                    return depth;
                }
                
                if (tn->left) {
                    bfsQ.push(tn->left);
                }
                if (tn->right) {
                    bfsQ.push(tn->right);
                }
            }
            // Next level
            ++depth;
        }
        // Error
        return -1;
    }
};
