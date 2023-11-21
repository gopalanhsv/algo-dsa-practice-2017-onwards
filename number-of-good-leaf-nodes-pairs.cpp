// n => num tree nodes, d => distance
// Time complexity : O(nd)
// Space complexity : O(max(n, d))

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
    countPairs(TreeNode* root, int distance) {
        if (!root) {
            // Empty tree
            return 0;
        }

        // Exec a postorder DFS traversal of the tree, computing the number of
        // good leaf pairs at each subtree; while tracking the number of leaf nodes
        // within specified 'distance' from subtree root
        vector<int> distToLeafCntV(distance + 1, 0);
        return countPairsDfsRec(root, distance, distToLeafCntV);
    }
    
private:
    
    int
    countPairsDfsRec(TreeNode* currNode, int distance, vector<int>& distToLeafCntV) {
        // Visit left/right subtree of current node recursively.
        // Determine the number of good leaf pairs in the subtrees rooted at left/right child
        // respectively; and also the number of leaf nodes lying in the left/right subtree
        // within specified 'distance' from current subtree root i.e. 'currNode'
        auto lSubtreeGoodLeafPairs = 0;
        vector<int> lSubtreeLeafCntV(distance + 1, 0);
        if (currNode->left) {
            lSubtreeGoodLeafPairs =
                countPairsDfsRec(currNode->left, distance, lSubtreeLeafCntV);
        }
        auto rSubtreeGoodLeafPairs = 0;
        vector<int> rSubtreeLeafCntV(distance + 1, 0);
        if (currNode->right) {
            rSubtreeGoodLeafPairs =
                countPairsDfsRec(currNode->right, distance, rSubtreeLeafCntV);
        }

        // Compute the number of good leaf node pairs in the subtree rooted at current root;
        // and the count of leaf nodes located within specified 'distance' from subtree parent
        // i.e. parent of 'currNode'.
        int nGoodLeafPairs = lSubtreeGoodLeafPairs + rSubtreeGoodLeafPairs;
        if (!currNode->right && !currNode->left) {
            // Current node is sole leaf node at distance '1' from its parent
            distToLeafCntV[1] = 1;
        } else {
            // Current node is an internal node
            // Accoount for all the good leaf pairs formed from the leaf nodes lying in
            // the left subtree with those in right subtree (path via currNode between 
            // leaf nodes with max len of distance)
            // ld => distance to left subtree leaf node
            // rd => distance to right subtree leaf node
            // ld + rd <= distance;
            // => rd <= distance - ld
            for (int ld = 0; ld <= distance; ++ld) {
                for (int rd = 0; rd <= distance - ld; ++rd) {
                    nGoodLeafPairs += (lSubtreeLeafCntV[ld] * rSubtreeLeafCntV[rd]);
                }
            }
            // Determine the count of all leaf nodes lying at all distances in range [1, 'distance - 1']
            // from current subtree root/currNode; i.e. at all distances in range [2, distance]
            // from currNode parent
            for (int d = 2; d < distance; ++d) {
                distToLeafCntV[d] = lSubtreeLeafCntV[d - 1] + rSubtreeLeafCntV[d - 1];
            }
        }
        
        return nGoodLeafPairs;
    }
};
