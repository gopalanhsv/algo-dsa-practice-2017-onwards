// Time complexity : O(num nodes)
// Space complexity : O(tree height) -> O(num nodes)

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
    longestZigZag(TreeNode* root) {
        if (!root) {
            // Base case of null/empty tree
            return 0;
        }

        return longestZigZagViaDFS(root);
    }
    
private:
    
    
    void
    longestZigZagViaDFS(
        TreeNode* node, bool nodeIsLeftChild, int nNodesOnPathToNode, int & maxNumPathNodesSeen) {
        
        // Update the max number of nodes seen in a zigzag path by including the
        // zigzag path to current node from its parent node
        maxNumPathNodesSeen = max(maxNumPathNodesSeen, nNodesOnPathToNode);
        
        if (node->left) {
            // Visit the left subtree of current node. Visit all the nodes. Determine the number of
            // nodes in all the zigzag paths in left subtree; keeping track of zigzag paths with
            // max number of nodes
            if (!nodeIsLeftChild) {
                // Current node is right child of parent. So current nodes' left child continues
                // the zigzag path which comes to current node from its parent
                longestZigZagViaDFS(node->left, true, nNodesOnPathToNode + 1, maxNumPathNodesSeen);
            } else {
                // Current node is left child of parent. So current node terminates the zigzag path
                // which comes to current node from its parent
                // Commence a new zigzag path from current node to its left child (has 2 nodes 
                // initially - current node and its left child)
                longestZigZagViaDFS(node->left, true, 2, maxNumPathNodesSeen);
            }
        }

        if (node->right) {
            // Visit the right subtree of current node. Visit all the nodes. Determine the number of
            // nodes in all the zigzag paths in right subtree; keeping track of zigzag paths with
            // max number of nodes
            if (nodeIsLeftChild) {
                // Current node is left child of parent. So current nodes' right child continues
                // the zigzag path which comes to current node from its parent
                longestZigZagViaDFS(node->right, false, nNodesOnPathToNode + 1, maxNumPathNodesSeen);
            } else {
                // Current node is right child of parent. So current node terminates the zigzag path
                // which comes to current node from its parent
                // Commence a new zigzag path from current node to its right child (has 2 nodes 
                // initially - current node and its right child)
                longestZigZagViaDFS(node->right, false, 2, maxNumPathNodesSeen);
            }
        }        
    }
    
    int
    longestZigZagViaDFS(TreeNode* root) {
        // Root => 1 node
        int nPathNodesToRoot = 1;
        // Tracks the max number of nodes amongst all zigzag path explored so far
        int maxNumPathNodesSeen = nPathNodesToRoot;
        
        if (root->left) {
            // Visit the left subtree of root. Visit all the nodes. Determine the number of
            // nodes in all the zigzag paths in left subtree; keeping track of zigzag paths with
            // max number of nodes
            longestZigZagViaDFS(root->left, true, nPathNodesToRoot + 1, maxNumPathNodesSeen);
        }
        if (root->right) {
            // Visit the right subtree of root. Visit all the nodes. Determine the number of
            // nodes in all the zigzag paths in right subtree; keeping track of zigzag paths with
            // max number of nodes
            longestZigZagViaDFS(root->right, false, nPathNodesToRoot + 1, maxNumPathNodesSeen);
        }
        // Max zigzag path len (1 less that zigzag path with max nodes)
        return maxNumPathNodesSeen - 1;
    }
};
