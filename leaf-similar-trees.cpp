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
    bool
    leafSimilar(TreeNode* root1, TreeNode* root2) {
        if (!root1 || !root2) {
            return root2 == root1;
        }
        
        
        return leafSimilarUsingStacks(root1, root2);
        
        //return leafSimilarComplicated(root1, root2);
    }

private:
    bool
    leafSimilarUsingStacks(TreeNode* root1, TreeNode* root2) {
        // Perform a preorder DFS traversal (since we need to
        // compare left leaf prior to right leaf) and compare the
        // two tree leaves in lockstep from left to right
        stack<TreeNode*> dfsStk1;
        stack<TreeNode*> dfsStk2;
        dfsStk1.push(root1);
        dfsStk2.push(root2);
        while (!dfsStk1.empty() && !dfsStk2.empty()) {
            if (nextLeaf(dfsStk1) != nextLeaf(dfsStk2)) {
                return false;
            }
        }
        
        // Both the stacks should be empty at this point for
        // similar leaves and no left/unvisited nodes
        return (dfsStk1.empty() && dfsStk2.empty());
    }
    
    int
    nextLeaf(stack<TreeNode*>& dfsStk) {
        // Preorder to get the next leaf
        while (true) {
            auto tn = dfsStk.top();
            dfsStk.pop();
            // Preorder leaf visit should be L and then R, so add
            // to stack in reverse order
            if (tn->right) {
                dfsStk.push(tn->right);
            }
            if (tn->left) {
                dfsStk.push(tn->left);
            }
            // Popped node is leaf => this is the next leaf
            if (!tn->left & !tn->right) {
                return tn->val;
            }
        }
    }
    
    bool
    leafSimilarComplicated(TreeNode* root1, TreeNode* root2) {
        
        // Find all leaves in tree 1
        findLeaves(root1);
        
        // Verify if leaves in tree 2 occur in same order as 1
        _leavesVecIdx = 0;
        if (!verifyIfLeavesOccurInSameOrder(root2)) {
            return false;
        }
        return _leavesVecIdx == _leavesV.size();
    }
    
    void
    findLeaves(TreeNode* cn) {
        // Visit node and check if it is leaf
        if (!cn->left && !cn->right) {
            // Leaf node
            _leavesV.emplace_back(cn->val);
            cout << cn->val << " ";
            return;
        }
        
        // Check for leaves in left subtree
        if (cn->left) {
            findLeaves(cn->left);
        }
        
        // Check for leaves in right subtree
        if (cn->right) {
            findLeaves(cn->right);
        }
    }
    
    bool
    verifyIfLeavesOccurInSameOrder(TreeNode* cn) {
        // Visit node and check if it is leaf
        if (!cn->left && !cn->right) {
            // Leaf node
            // Verify in this leaf val and expected val as per vector are
            // same
            return (_leavesV[_leavesVecIdx++] == cn->val);
        }
        
        // Verify leaves in left subtree
        if (cn->left) {
            if (!verifyIfLeavesOccurInSameOrder(cn->left)) {
                return false;
            }
        }
        
        // Verify leaves in right subtree
        if (cn->right) {
            if (!verifyIfLeavesOccurInSameOrder(cn->right)) {
                return false;
            }
        }
        
        return true;
    }
    
    // Data members
    // Leaves vector for tree1
    vector<int> _leavesV;
    // Leaves vector index for verification pass
    vector<int>::size_type _leavesVecIdx;
};
