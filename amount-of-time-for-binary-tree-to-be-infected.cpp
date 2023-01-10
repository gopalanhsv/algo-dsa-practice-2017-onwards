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
    amountOfTime(TreeNode* root, int start) {
        // Since infection commencing from 'start' node at time 0 spreads to the
        // adjacent connected uninfected node at each new minute tick, the problem
        // can be modelled as a graph traversal problem with traversal commencing at
        // 'start' node; moving one edge outwards every minute from an infected
        // node to adjacent uninfected node till all nodes are infected. This
        // corresponds to BFS traversal commencing at 'start' node and computing the
        // total number of levels to visit all nodes
        
        // Build an undirected graph from the tree via DFS
        buildGraphViaDfs(root);
        
        return amountOfTimeViaBfs(start);
    }
    
private:
    
    // Data members
    void
    buildGraphViaDfs(TreeNode* currNode) {
        
        auto currNodeVal = currNode->val;
        
        // Left child
        auto lChild = currNode->left;
        if (lChild) {
            // Add bidirectional edge between current node and its left child 
            _adjListTbl[currNodeVal].emplace_back(lChild->val);
            _adjListTbl[lChild->val].emplace_back(currNodeVal);
            // Visit and build graph rooted at left subtree
            buildGraphViaDfs(lChild);
        }
        
        // Right child
        auto rChild = currNode->right;
        if (rChild) {
            // Add bidirectional edge between current node and its right child 
            _adjListTbl[currNodeVal].emplace_back(rChild->val);
            _adjListTbl[rChild->val].emplace_back(currNodeVal);
            // Visit and build graph rooted at right subtree
            buildGraphViaDfs(rChild);
        }
    }

    int
    amountOfTimeViaBfs(int sv) {
        queue<int> bfsQ;
        typedef queue<int>::size_type qSzT;
        unordered_set<int> visited;
        
        // Commence BFS vertex 'sv'
        visited.insert(sv);
        bfsQ.push(sv);
        int nLevels = 0;
        
        while (!bfsQ.empty()) {
            
            // Visit/infect all uninfected vertices at current level
            qSzT currLvlSz = bfsQ.size();
            for (int i = 0; i != currLvlSz; ++i) {
                // Visit/infect the vertex at BFS Q front
                auto cv = bfsQ.front();
                bfsQ.pop();

                // Iterate over all neighbour vertices of current vertex
                auto & nbrV = _adjListTbl[cv];
                for (auto & nv : nbrV) {
                    // Set up all the unvisited/uninfected neighbors of current
                    // vertex for a BFS visit/infection in next iteration
                    if (visited.find(nv) == visited.end()) {
                        bfsQ.push(nv);
                        visited.insert(nv);
                    }
                }
            }
            
            // Increment number of minutes/levels
            ++nLevels;
        }
        
        return nLevels - 1;
    }
    
    // Adjacency list representation of graph/tree
    unordered_map<int, vector<int> > _adjListTbl;
    
};
