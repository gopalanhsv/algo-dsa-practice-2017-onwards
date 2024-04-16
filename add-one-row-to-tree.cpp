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
    TreeNode*
    addOneRow(TreeNode* root, int val, int depth) {
        
        if (1 == depth) {
            // Base case of depth as '1' (as tree root changes)
            TreeNode* newRoot = new TreeNode(val, root, nullptr);
            return newRoot;
        }

        // Do a BFS/level order traversal of the tree
        //return addOneRowBFS(root, val, depth);
        // Do a DFS traversal of the tree
        return addOneRowDFS(root, val, depth);
    }
    
private:
    
    TreeNode*
    addOneRowBFS(TreeNode* root, int val, int depth) {
        
        // Do a BFS/level order traversal of the tree
        // till the 'depth - 1' level. For each of the nodes at this
        // level 'depth - 1', add the new value 'val' as :-
        // 1. A new left child between the node and its earlier left child AND
        // 2. A new right child between the node and its earlier right child
        queue<TreeNode*> bfsQ;
        // Commence BFS
        bfsQ.push(root);
        int level = 1;
        while (!bfsQ.empty()) {
            auto currLvlSz = bfsQ.size();
            // Iterate over all nodes at the current level
            for (auto i = 0; i != currLvlSz; ++i) {
                // Dequeue the node at Q front
                auto tn = bfsQ.front();
                bfsQ.pop();
                
                if (level == depth - 1) {
                    // Traversal is at the level where insertion has to be done
                    // Insert new node 'val' between the dequeued node and 
                    // each of its children
                    // 1. A new left child between dequeued node and its earlier left child
                    // 2. A new right child between dequeued node and its earlier right child
                    tn->left = new TreeNode(val, tn->left, nullptr);
                    tn->right = new TreeNode(val, nullptr, tn->right);
                    // No need to explore beyond this level
                } else {
                    // Set up the left and right child of dequeued node
                    // for traversal in the next iteration
                    if (tn->left) {
                        bfsQ.push(tn->left);
                    }
                    if (tn->right) {
                        bfsQ.push(tn->right);
                    }
                }
            }
            // Update level
            ++level;
        }
        
        return root;
    }
    
    void
    addOneRowDFSRec(TreeNode* currNode, int val, int depth, int currDepth) {
        if (currDepth == depth - 1) {
            // Traversal is at the depth where insertion has to be done
            // Insert new node 'val' between the current node and 
            // each of its children
            // 1. A new left child between current node and its earlier left child
            // 2. A new right child between current node and its earlier right child
            currNode->left = new TreeNode(val, currNode->left, nullptr);
            currNode->right = new TreeNode(val, nullptr, currNode->right);
            
            // Reached required level, nothing more to be done
            return;
        }
        
        // Visit the left subtree and exec insertion at the appropriate depth
        if (currNode->left) {
            addOneRowDFSRec(currNode->left, val, depth, currDepth + 1);
        }
        // Visit the right subtree and exec insertion at the appropriate depth
        if (currNode->right) {
            addOneRowDFSRec(currNode->right, val, depth, currDepth + 1);
        }
    }
    
    TreeNode*
    addOneRowDFS(TreeNode* root, int val, int depth) {
        addOneRowDFSRec(root, val, depth, 1);
        return root;
    }
};
