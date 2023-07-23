// Time complexity : O(2^(n / 2))
// Space complexity : O(nx(2^(n / 2)))

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
    allPossibleFBT(int n) {
        if (n % 2 == 0) {
            // Base case of even/zero nodes => FBT impossible
            return {};
        }
        
        return generateAllFullBinarySubtrees(n);
    }
    
private:
    
    TreeNode*
    cloneTree(TreeNode * root) {
        // Creates a deep copy of the tree 
        if (!root) {
            return root;
        }
        
        TreeNode *newRoot = new TreeNode(0);
        newRoot->left = root->left ? cloneTree(root->left) : nullptr;
        newRoot->right = root->right ? cloneTree(root->right) : nullptr;
        return newRoot;
    }
    
    vector<TreeNode*>
    generateAllFullBinarySubtrees(int n) {

        // Check if FB subtrees already available for given number of nodes
        unordered_map<int, vector<TreeNode*> >::iterator tblIter;
        tblIter = _numNodesToFBTListTbl.find(n);
        if (tblIter != _numNodesToFBTListTbl.end()) {
            // Subtrees available in table, return the same
            return tblIter->second;
        }
        
        vector<TreeNode*> subTreeRootV;
        
        // Single node
        if (n == 1) {
            subTreeRootV.emplace_back(new TreeNode(0, nullptr, nullptr));
            _numNodesToFBTListTbl[n] = subTreeRootV;
            return _numNodesToFBTListTbl[n];
        }
        
        // More than 1 node
        
        // Create a root
        // Generate all left subtrees with either 1 or odd number of nodes
        // Generate all right subtrees with either 1 or odd number of nodes
        for (int nLeftNodes = 1; nLeftNodes <= n - 1; nLeftNodes += 2) {
            
            // Generate all left subtrees
            vector<TreeNode*> leftSubTreeRootV = 
                generateAllFullBinarySubtrees(nLeftNodes);
            
            // Generate all right subtrees
            vector<TreeNode*> rightSubTreeRootV =
                generateAllFullBinarySubtrees(n - 1 - nLeftNodes);
            
            // Iterate over all created left subtrees
            for (auto & lSubRoot : leftSubTreeRootV) {
                // Iterate over all created right subtrees
                for (auto & rSubRoot : rightSubTreeRootV) {
                    // Create a FBT with a new root and a cloned/deep copy
                    // selection of possible FB subtrees for left and right
                    TreeNode * subTreeRoot = 
                        new TreeNode(0, cloneTree(lSubRoot), cloneTree(rSubRoot));
                    subTreeRootV.emplace_back(subTreeRoot);
                }
            }
        }
        
        // Cache the list of subtrees generated for given number of nodes
        _numNodesToFBTListTbl[n] = subTreeRootV;
        return subTreeRootV;
    }
    
private:

    // Hash table/cache mapping number of tree nodes to respective set of
    // FBTs for the given number of nodes. Done to prevent recalculation
    // of subtrees for a certain number of nodes again and again.
    unordered_map<int, vector<TreeNode*> > _numNodesToFBTListTbl;
};
