// Time complexity : O(num tree nodes)
// Space complexity :
// O(num tree nodes) for skewed tree
// O(log(num tree nodes)) otherwise

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
    buildTree(vector<int>& preorder, vector<int>& inorder) {
        
        // Preorder traversal recursively is subtree-root -> L-subtree -> R-subtree
        // Inorder traversal recursively is L-subtree -> subtree-root -> R-subtree
        // 1. preorder[0] gives the root node val; looking up the same node in inorder
        // traversal gives an index 'x'.
        // 2. Elements to the left of index 'x', i.e. range [0, x - 1] will
        // form the left subtree of root; and
        // 3. Elements to the right of 'x', i.e range [x + 1, inorder.size() - 1]
        // will form the right subtree of root.
        // 4. Incrementing the preorder index to 1 gives preorder[1] which is
        // the value of next subtree root. If range [0, x - 1] found in step 2
        // is valid (i.e has elements), preorder[1] will give the subtree root
        // for this range.
        // Otherwise, preorder[1] is the subtree root for range [x + 1, inorder.size() - 1]
        // Recursively applying the above steps allows the tree to be constructed
        // via divide and conquer
        
        // Contruct hash table mapping for quick lookup of the inorder index for
        // an element as seen in preorder
        int numNodes = inorder.size();
        for(int i = 0; i != numNodes; ++i) {
            _inorderValToIdxTbl[inorder[i]] = i;
        }
        
        // Recursively build the tree using inorder elements in range
        // [0, numNodes - 1] with root at preorder[0]
        return buildTree(preorder, inorder, 0, numNodes - 1, 0);
    }
    
private:

    TreeNode*
    buildTree(vector<int>& preorder, vector<int>& inorder,
              int l, int r, int preOrderIdx) {
        
        // Recursively build the subtree tree using inorder elements in range
        // [l, r] with root being preorder[preOrderIdx]
    
        if (l == r) {
            // Range is of 1 element, so construct and return a single
            // node subtree with root as inorder[l]/preorder[preorderIdx]
            return new TreeNode(inorder[l]);
        } else if (l > r) {
            // No element in range; so subtree is null/empty
            return nullptr;
        }
        
        // Subtree
        // Subtree root consists of element in range [l, r]
        // with root being preorder[preOrderIdx]
        int subTreeRootVal = preorder[preOrderIdx];
        
        // Lookup the root location/index in inorder array
        // Left subtree will consist of [l, rootIdx - 1] elements from inorder array
        // Right subtree will consist of [rootIdx + 1, r] elements from inorder array
        int rootIdx = _inorderValToIdxTbl[subTreeRootVal];
        
        // Advance to next root element by incrementing preorderIdx
        preOrderIdx += 1;
        // Recursively build left subtree from inorder elements [l, rootIdx - 1]
        // with root at preOrderIdx
        TreeNode *lSubtree =
            buildTree(preorder, inorder, l, rootIdx - 1, preOrderIdx);
        
        // Advance to next root element by incrementing preorderIdx
        // by number of elements in the left subtree constructed above
        preOrderIdx += rootIdx - l;
        // Recursively build right subtree from inorder elements [rootIdx + 1, r]
        // with root at preOrderIdx
        TreeNode *rSubtree =
            buildTree(preorder, inorder, rootIdx + 1, r, preOrderIdx);
        
        // Crete subtree rooted at preorder[preorderIdx] and
        // inorder elements [l, r] using the left and rigth subtrees created above
        TreeNode *subtreeRoot = new TreeNode(subTreeRootVal, lSubtree, rSubtree);
        
        return subtreeRoot;
    }
    
    // Data members

    // Table mapping inorder traversal array elements to
    // their respective index locations
    unordered_map<int, int> _inorderValToIdxTbl;

};
