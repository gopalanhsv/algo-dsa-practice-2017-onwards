// n1 => Num tree#1 nodes, n2 => Num tree#2 nodes
// Two Pointer Approach
// Time complexity : O(n1 + n2)
// Space complexity : O(n1 + n2)

// DFS Approach
// Time complexity : O(n1 + n2 x log n1)
// Space complexity : O(n1 + n2) if tree is unbalanced
// Space complexity : O(log n1 + log n2) if tree is balanced

// Hash Table Approach
// Time complexity : O(n1 + n2)
// Space complexity : O(n1 + n2)

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
    twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        if (!root1 || !root2) {
            return false;
        }
        
        //return twoSumBSTsViaTwoPointer(root1, root2, target);
        return twoSumBSTViaHashTable(root1, root2, target);
        //return twoSumBSTsViaDFS(root1, root2, target);
    }
    
private:
    
    void
    inorderBSTRec(TreeNode* currNode, vector<long>& treeElemsV) {
        // Visit the left subtree
        if (currNode->left) {
            inorderBSTRec(currNode->left, treeElemsV);
        }
        
        // Visit the node
        treeElemsV.emplace_back(currNode->val);
        
        // Visit the right subtree
        if (currNode->right) {
            inorderBSTRec(currNode->right, treeElemsV);
        }
    }

    bool
    twoSumBSTsViaTwoPointer(TreeNode* root1, TreeNode* root2, int target) {
        // Build 2 sorted arrays of elements in the respective
        // BSTs via inorder traversal
        vector<long> tree1ElemsV, tree2ElemsV;
        inorderBSTRec(root1, tree1ElemsV);
        inorderBSTRec(root2, tree2ElemsV);
        // Position two pointers:- one at the lower end of the array#1 and
        // the other at the higher end of array#2
        int n1 = tree1ElemsV.size();
        int n2 = tree2ElemsV.size();
        int lo = 0;
        int hi = n2 - 1;
        // Narrow the search range by moving the pointers towards
        // each other till target is hit OR one of pointers hits the
        // respective array end
        while ((lo < n1) && (hi >= 0)) {
            long candidateSum = tree1ElemsV[lo] + tree2ElemsV[hi]; 
            if (candidateSum == target) {
                // Found target
                return true;
            } else if (candidateSum > target) {
                // Need to decrease sum. Reduce 'hi'
                --hi;
            } else {
                // Need to increase sum. Increase 'lo'
                ++lo;
            }
        }
        
        return false;
    }
    
    bool
    targetInBST(TreeNode* root, int target) {
        TreeNode* currNode = root;
        while (currNode) {
            auto val = currNode->val;
            if (val > target) {
                // Search for lower values in left subtree of currNode
                currNode = currNode->left;
            } else if (val < target) {
                // Search for higher values in right subtree of currNode
                currNode = currNode->right;
            } else {
                // Target found
                return true;
            }
        }
        return false;
    }
    
    bool
    twoSumDFSRec(TreeNode* currNode, TreeNode* root2, int target) {
        // Search of 'target' sum in left subtree of currNode in tree#1
        if ((currNode->left) &&
            twoSumDFSRec(currNode->left, root2, target)) {
            return true;
        }

        // Visit the current node and check for complementary value
        // presence in the other tree
        if (targetInBST(root2, target - currNode->val)) {
            return true;
        }
        
        // Search of 'target' sum in right subtree of currNode in tree#1
        if ((currNode->right) &&
            twoSumDFSRec(currNode->right, root2, target)) {
            return true;
        }
        
        return false;
    }
    
    bool
    twoSumBSTsViaDFS(TreeNode* root1, TreeNode* root2, int target) {
        // Do a DFS traversal of one of the trees. For each node, find if
        // the complementary value (target - node value) exists in the
        // other tree via binary search
        
        return twoSumDFSRec(root1, root2, target);
    }

    bool
    twoSumBSTViaHashTable(TreeNode* root1, TreeNode* root2, int target) {
        // Exec DFS traversal of tree#1, storing each of the seen
        // node values in a hash table
        unordered_set<int> tree1ValsTbl;
        stack<TreeNode*> dfsStk;
        dfsStk.push(root1);
        while (!dfsStk.empty()) {
            // Visit the current node
            auto currNode = dfsStk.top();
            dfsStk.pop();
            tree1ValsTbl.insert(currNode->val);
            
            // Set up right subtree for DFS traversal
            if (currNode->right) {
                dfsStk.push(currNode->right);
            }
            // Set up left subtree for DFS traversal
            if (currNode->left) {
                dfsStk.push(currNode->left);
            }
        }
        
        // Iterate through each of tree#2 nodes and search
        // for the complementary target value in the hash table
        dfsStk.push(root2);
        while (!dfsStk.empty()) {
            // Visit the current node
            auto currNode = dfsStk.top();
            dfsStk.pop();
            
            // Check for presence of complementary value adding upto target
            if (tree1ValsTbl.find(target - currNode->val) != tree1ValsTbl.end()) {
                // Found vals in disjoint trees adding upto target
                return true;
            }
            
            // Set up right subtree for DFS traversal
            if (currNode->right) {
                dfsStk.push(currNode->right);
            }
            // Set up left subtree for DFS traversal
            if (currNode->left) {
                dfsStk.push(currNode->left);
            }
        }
        
        return false;
    }
};
