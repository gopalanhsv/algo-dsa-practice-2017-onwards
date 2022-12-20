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

#define BFS

class Solution {
public:
    vector<int>
    rightSideView(TreeNode* root) {
        if (!root) {
            // Base case of empty tree
            return _rtViewV;
        }

#ifdef BFS
        rightSideViewViaBFS(root);
#endif
        
#ifdef DFS
        rightSideViewViaDFS(root, 1);
#endif

        return _rtViewV;
    }
    
private:

    void
    rightSideViewViaDFS(TreeNode* currNode, int currDepth) {
        // Do a DFS traversal of the tree by visiting the right subtree followed
        // by the left subtree at each node. Since the right subtree is visited
        // prior to left subtree at each level; the first node visited at each
        // new level/depth of the tree would be the right side view node for
        // that particular depth/level
        
        if (currDepth > _rtViewV.size()) {
            // First node visited at each new depth/level
            _rtViewV.emplace_back(currNode->val);
        }

        // Visit the right subtree of current node
        if (currNode->right) {
            rightSideViewViaDFS(currNode->right, currDepth + 1);
        }

        // Visit the left subtree of current node
        if (currNode->left) {
            rightSideViewViaDFS(currNode->left, currDepth + 1);
        }
    }

    void
    rightSideViewViaBFS(TreeNode* root) {
        // Do a level order traversal of the tree. Last node
        // visited at each level would be the right side view
        // node for the particular level
        
        // Commence BFS by adding root to BFS Q
        queue<TreeNode*> bfsQ;
        bfsQ.push(root);
        while (!bfsQ.empty()) {
            
            // Node at back of queue is the right side view node for current level
            auto & bn = bfsQ.back();
            _rtViewV.emplace_back(bn->val);
            
            // Visit all nodes at current level 
            int currLvlSz = bfsQ.size();
            for (int i = 0; i != currLvlSz; ++i) {
                // Deque node at BFS Q front and schedule its child nodes for
                // BFS traversal in next iteration by appending them to BFS Q
                auto & tn = bfsQ.front();
                if (tn->left) {
                    bfsQ.push(tn->left);
                }
                if (tn->right) {
                    bfsQ.push(tn->right);
                }
                    
                // Popping off the dequeued node here for perf efficiency
                bfsQ.pop();
            }
        }
    }
    
    // Data members
    // Array of right side view nodes
    vector<int> _rtViewV;
};
