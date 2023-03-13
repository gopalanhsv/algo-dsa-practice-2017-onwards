// Recursive approach
// Time Complexity : O(num tree nodes)
// Space Complexity : O(tree height) stack

// Iterative approach
// Time Complexity : O(num tree nodes)
// Space Complexity : O(num tree nodes) queue

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
    bool
    isSymmetric(TreeNode* root) {
        // Given tree is symmetric if its either empty or its subtrees are symmetric
        return (nullptr == root) ||
            areSubtreesSymmetricRecursive(root->left, root->right);
            //areSubtreesSymmetricIterative(root->left, root->right);
    }

private:
    
    bool
    areSubtreesSymmetricRecursive(TreeNode* subtree1, TreeNode* subtree2) {
        if (!subtree1 && !subtree2) {
            // Both subtrees are empty => they are symmetrical 
            return true;
        }

        if (subtree1 && subtree2) {
            // Both subtrees are non-null, check if their respective roots have same values
            // and for symmetricity of L child of one with R child of another
            return (subtree1->val == subtree2->val) &&
                (areSubtreesSymmetricRecursive(subtree1->left, subtree2->right)) &&
                (areSubtreesSymmetricRecursive(subtree1->right, subtree2->left));
        }
        
        // One subtree is empty and other is not => assymmetric subtrees
        return false;
    }
    
    bool
    areSubtreesSymmetricIterative(TreeNode* subtree1, TreeNode* subtree2) {
        // Level order traversal queue
        queue<TreeNode*> traversalQ;
        // Add the subtree roots to queue
        traversalQ.push(subtree1);
        traversalQ.push(subtree2);
        
        // Commence level order traversal to check for symmetricity
        while (!traversalQ.empty()) {
            // Dequeue the 2 subtrees nodes at front of traversal Q and check for
            // their symmetricity
            subtree1 = traversalQ.front();
            traversalQ.pop();
            subtree2 = traversalQ.front();
            traversalQ.pop();
            
            if (!subtree1 && !subtree2) {
                // Both dequeued nodes are null hence symmetric, continue to examine
                // other nodes
                continue;
            }
            
            if (!subtree1 || !subtree2) {
                // Only one of the 2 dequeued nodes is empty, implies asymmetricity
                return false;
            }
            
            // Both dequeued nodes are non-null, validate data and add their children
            // to traversal Q for further checks
            if (subtree1->val != subtree2->val) {
                return false;
            }
            
            traversalQ.push(subtree1->left);
            traversalQ.push(subtree2->right);
            traversalQ.push(subtree2->left);
            traversalQ.push(subtree1->right);

        }
        
        return true;
    }
};
