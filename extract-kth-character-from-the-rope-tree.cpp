// n => num nodes
// Time complexity : O(n) worst case/ O(logn) avg case 
// Space complexity : O(1)

/**
 * Definition for a rope tree node.
 * struct RopeTreeNode {
 *     int len;
 *     string val;
 *     RopeTreeNode *left;
 *     RopeTreeNode *right;
 *     RopeTreeNode() : len(0), val(""), left(nullptr), right(nullptr) {}
 *     RopeTreeNode(string s) : len(0), val(std::move(s)), left(nullptr), right(nullptr) {}
 *     RopeTreeNode(int x) : len(x), val(""), left(nullptr), right(nullptr) {}
 *     RopeTreeNode(int x, RopeTreeNode *left, RopeTreeNode *right) : len(x), val(""), left(left), right(right) {}
 * };
 */
class Solution {
public:
    char
    getKthCharacter(RopeTreeNode* root, int k) {
    
        // Only "node.len" chars need to considered S[node] post concatenation of
        // the child node vals at each node. This makes the Rope structure like
        // a BST in terms of searching for the 'kth' root char
        
        auto currNode = root;
        while (currNode->len != 0) {
            auto lChild = currNode->left;
            auto lSubtreeStrLen = 0;
            
            // Check if the 'k'th char is in left or right subtree
            if (lChild) {
                
                if (0 == lChild->len) {
                    // Left child is a leaf
                    if (lChild->val.size() >= k) {
                        // Left child contains the kth char
                        // Advance to left child for next iteration
                        currNode = currNode->left;
                        continue;
                    } else {
                        // Left child does not contain the kth char
                        // Account for the number of chars in the left subtree string
                        lSubtreeStrLen = lChild->val.size();
                    }
                } else {
                    // Left child is an internal node
                    if (lChild->len >= k) {
                        // Left subtree contains the kth char
                        // Advance to left child for next iteration
                        currNode = currNode->left;
                        continue;
                    } else {
                        // Left subtree does not contain the kth char
                        // Account for the number of chars in the left subtree string
                        lSubtreeStrLen = lChild->len;
                    }
                }
            }
            
            // Right subtree contains the 'k'th char
            // Adjust 'k' to account for chars in the left subtrees/leaves
            k -= lSubtreeStrLen;
            currNode = currNode->right;
        }
        
        // Reached the leaf node containing the 'k'th char
        auto & leafNodeStr = currNode->val;
        return leafNodeStr[k - 1];
    }
};
