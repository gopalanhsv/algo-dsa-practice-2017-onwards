// n => num vertices, e => edges.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    vector<int>
    findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (1 == n) {
            return vector<int>({0});
        }
        // Minimum Height Trees would be those whose roots are located at the graph
        // centre -- as from the tree/graph center all the leaf nodes would be
        // equidistant (except for +-1 offset) => problem reduces to finding the center
        // nodes of the graph/tree. This is easily computed via topological sort
        
        // Construct the graph/tree adjacency list and also the degree vector
        // maintaining the number of edges incident on a vertex
        vector<int> degreeV(n, 0);
        unordered_map<int, vector<int> > adjList;
        for (auto & edge : edges) {
            // Edge between vertices v1, v2
            auto & v1 = edge[0];
            auto & v2 = edge[1];
            degreeV[v1]++;
            degreeV[v2]++;
            adjList[v1].emplace_back(v2);
            adjList[v2].emplace_back(v1);
        }
        
        // To determine the tree center:-
        // 1. Find all vertices with only a single edge incident on them
        // (i.e. leaf nodes with indegree 1) and add them to TS queue.
        // 2. Remove these leaf nodes from the graph/tree (removal consists
        // of removing the edges commencing from these leaf nodes).
        // 3. Vertex/edge removal operation will result in a new set of leaf vertices
        // Repeat algo from step 1 till only 1 or 2 nodes are present in the graph
        // after multiple leaf node removals.
        // The remaining 1/2 nodes would be the tree center and root of graph MHTs
        
        // Leaf nodes added to queue
        queue<int> leafNodesQ;
        for (auto v = 0; v != n; ++v) {
            if (1 == degreeV[v]) {
                leafNodesQ.push(v);
            }
        }

        // Prune all leaf nodes at a particular level from outside tree to inside like
        // spider web till only one/two nodes are left.
        typedef queue<int>::size_type qSzT;
        int nRemovedNodes = 0;
        while (!leafNodesQ.empty() && (nRemovedNodes < n - 2)) {
            // Remove all leaf nodes at current level and edges incident on them
            auto qSz = leafNodesQ.size();
            for (auto i = 0; i != qSz; ++i) {
                // Dequeue node at queue front
                auto v = leafNodesQ.front();
                leafNodesQ.pop();
                
                // Remove leaf node (i.e. remove all edges incident on node)
                ++nRemovedNodes;
                
                for (auto & nv : adjList[v]) {
                    if (1 == --degreeV[nv]) {
                        // Removal of edge v -> nv results in new leaf node 'nv' 
                        leafNodesQ.push(nv);
                    }
                }
            }            
        }
        
        // Remaining 1/2 leaf nodes in Q would be the tree center
        vector<int> treeCenterV;        
        while (!leafNodesQ.empty()) {
            treeCenterV.emplace_back(leafNodesQ.front());
            leafNodesQ.pop();
        }
        return treeCenterV;
    }
};
