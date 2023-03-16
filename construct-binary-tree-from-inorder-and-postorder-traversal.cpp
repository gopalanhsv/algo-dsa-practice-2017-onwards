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
    buildTree(vector<int>& inorder, vector<int>& postorder) {
        
        // Postorder traversal recursively is L-subtree -> R-subtree -> subtree-root
        // Inorder traversal recursively is L-subtree -> subtree-root -> R-subtree
        // 1. postorder[postorder.size() - 1] gives the root node val; looking up
        // the same node in inorder traversal gives an index 'x'.
        // 2. Elements to the right of index 'x', i.e. range [x + 1, inorder.size() - 1]
        // will form the right subtree of root.
        // 3. Elements to the left of index 'x', i.e. range [0, x - 1] in
        // inorder array will form the left subtree of root; and
        // 4. Decrementing the postorder index by 1 gives postorder[postorder.size() - 2]
        // which gives the value of next subtree root.
        // If range [x + 1, inorder.size() - 1] found in step 2 is valid (i.e has elements),
        // postorder[postorder.size() - 2] will give the subtree root for this range.
        // Otherwise, postorder[postorder.size() - 2] gives the
        // subtree root for range [0, x - 1]
        // Recursively applying the above steps allows the tree to be constructed
        // via divide and conquer
        
        // Contruct hash table mapping for quick lookup of the inorder
        // index for an element as seen in postorder
        int numNodes = inorder.size();
        for(int i = 0; i != numNodes; ++i) {
            _inorderValToIdxTbl[inorder[i]] = i;
        }
        
        // Recursively build the tree using inorder elements in range
        // [0, numNodes - 1] with root at postorder[numNodes - 1]
        return buildTree(postorder, inorder, 0, numNodes - 1, numNodes - 1);
    }
    
private:

    TreeNode*
    buildTree(vector<int>& postorder, vector<int>& inorder,
              int l, int r, int postOrderIdx) {
        
        // Recursively build the subtree tree using inorder elements in range
        // [l, r] with root being postorder[postOrderIdx]
    
        if (l == r) {
            // Range is of 1 element, so construct and return a single
            // node subtree with root as inorder[l]/postorder[postOrderIdx]
            return new TreeNode(inorder[l]);
        } else if (l > r) {
            // No element in range; so subtree is null/empty
            return nullptr;
        }
        
        // Subtree
        // Subtree root consists of elements in range [l, r]
        // with root being postorder[postOrderIdx]
        int subTreeRootVal = postorder[postOrderIdx];
        
        // Lookup the root location/index in inorder array
        // Left subtree will consist of [l, rootIdx - 1] elements from inorder array
        // Right subtree will consist of [rootIdx + 1, r] elements from inorder array
        int rootIdx = _inorderValToIdxTbl[subTreeRootVal];
        
        // Advance to next root element by decrementing postOrderIdx
        --postOrderIdx;
        // Recursively build right subtree from inorder elements [rootIdx + 1, r]
        // with root at postOrderIdx
        TreeNode *rSubtree =
            buildTree(postorder, inorder, rootIdx + 1, r, postOrderIdx);
        
        // Advance to next root element by decrementing postOrderIdx
        // by number of elements in the right subtree constructed above
        postOrderIdx -= (r - (rootIdx + 1) + 1);
        // Recursively build left subtree from inorder elements [l, rootIdx - 1]
        // with root at postOrderIdx
        TreeNode *lSubtree =
            buildTree(postorder, inorder, l, rootIdx - 1, postOrderIdx);
        
        // Decrementing postorder index not required here (will be done by
        // the function instance which invoked this instance)
        
        // Create subtree rooted at postorder[postOrderIdx] and
        // inorder elements [l, r] using the left and right subtrees created above
        TreeNode *subtreeRoot = new TreeNode(subTreeRootVal, lSubtree, rSubtree);
        
        return subtreeRoot;
    }
    
    // Data members

    // Table mapping inorder traversal array elements to
    // their respective index locations
    unordered_map<int, int> _inorderValToIdxTbl;
};
