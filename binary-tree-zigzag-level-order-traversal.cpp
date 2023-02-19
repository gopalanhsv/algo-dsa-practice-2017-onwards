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
    vector<vector<int>>
    zigzagLevelOrder(TreeNode* root) {
        // Null tree
        if (!root) {
            return vector<vector<int> >();
        }
        
        return zigzagLevelOrderApproach2(root);
    }
    
private:

    vector<vector<int>>
    zigzagLevelOrderApproach1(TreeNode* root) {
        
        // Do a BFS traversal. Ensure that child nodes at each level
        // are pushed on to a stack during traversal of a level.
        // When all nodes at a particular level are visited, the child
        // nodes for the next traversal level are popped from stack and
        // queued up to the BFS Q. This ensures that next level traversal
        // direction is always opposite to current level traversal one.
        // Need to also have a flag to track next level traversal direction
        // so that child nodes may be pushed on to stack in correct order
        
        vector<vector<int> > outV;
        queue<TreeNode*> bfsQ;
        stack<TreeNode*> nextLevelNodesStk;
        typedef queue<TreeNode*>::size_type qSzT;
        // Flag tracking traversal direction for next level
        bool nextLevelLeftToRight = false;
        
        // Append root to BFS Q
        bfsQ.push(root);
        while (!bfsQ.empty()) {
            qSzT currLvlSz = bfsQ.size();
            vector<int> currLvlNodesV;
            // Visit all nodes at current level
            for (int i = 0; i != currLvlSz; ++i) {
                // Visit node at BFS Q front
                auto& tn = bfsQ.front();
                currLvlNodesV.emplace_back(tn->val);
                
                if (nextLevelLeftToRight) {
                    // Nxt level L->R, so R child followed by L child added to stack
                    if (tn->right) {
                        nextLevelNodesStk.push(tn->right);
                    }
                    if (tn->left) {
                        nextLevelNodesStk.push(tn->left);
                    }
                } else {
                    // Nxt level R->L, so L child followed by R child added to stack
                    if (tn->left) {
                        nextLevelNodesStk.push(tn->left);
                    }
                    if (tn->right) {
                        nextLevelNodesStk.push(tn->right);
                    }
                }
                // Pop here for perf efficiency
                bfsQ.pop();
            }

            // Toggle flag for next level visit direction
            nextLevelLeftToRight = !nextLevelLeftToRight;
            
            // Queue up nodes for next level visit from stack to Q
            while (!nextLevelNodesStk.empty()) {
                auto& tn = nextLevelNodesStk.top();
                bfsQ.push(tn);
                nextLevelNodesStk.pop();
            }
            
            outV.emplace_back(currLvlNodesV);
        }
        
        return outV;
    }

    vector<vector<int>>
    zigzagLevelOrderApproach2(TreeNode* root) {
        
        // Do a BFS traversal. 
        // Do the traversal from L->R at each BFS level
        // 1. For even numbered levels (0, 2, 4, ..), output the
        // node values in L to R direction -- same as traversal direction
        // Output nodes in the same order as traversal
        // 2. For odd numbered levels (1, 3, 5, ..), output the
        // node values in R to L direction -- opposite to traversal
        // direction. Store node values in stack during traversal, and
        // then output the nodes from the stack in reverse traversal
        // direction
        
        vector<vector<int> > outV;
        queue<TreeNode*> bfsQ;
        stack<int> levelNodesStk;
        typedef queue<TreeNode*>::size_type qSzT;
        // Flag tracking node vals output direction for current traversal level
        bool leftToRight = true;
        
        // Append root to BFS Q
        bfsQ.push(root);
        while (!bfsQ.empty()) {
            qSzT currLvlSz = bfsQ.size();
            vector<int> currLvlNodesV;
            // Visit all nodes at current level
            for (int i = 0; i != currLvlSz; ++i) {
                // Visit node at BFS Q front
                auto& tn = bfsQ.front();

                // Setup the current nodes' children for BFS traversal
                // in next iteration
                if (tn->left) {
                    bfsQ.push(tn->left);
                }
                if (tn->right) {
                    bfsQ.push(tn->right);
                }
                
                // Output the current node value
                if (leftToRight) {
                    // Output identical to traversal direction
                    currLvlNodesV.emplace_back(tn->val);
                } else {
                    // Output reverse to traversal direction
                    // Add node value to stack
                    levelNodesStk.push(tn->val);
                }
                
                // Pop here for perf efficiency
                bfsQ.pop();
            }

            // Toggle flag for next level visit direction
            leftToRight = !leftToRight;
            
            // Output from stack reverse to traversal direction
            // for odd numbered levels
            while (!levelNodesStk.empty()) {
                auto & tnVal = levelNodesStk.top();
                currLvlNodesV.emplace_back(tnVal);
                levelNodesStk.pop();
            }
            
            outV.emplace_back(currLvlNodesV);
        }
        
        return outV;
    }
};
