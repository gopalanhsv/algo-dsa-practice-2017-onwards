// n => num graph nodes, e => num graph edges
// Time complexity : O(n + e)
// Space complexity : O(n + e)

class Solution {
public:
    vector<int>
    eventualSafeNodes(vector<vector<int>>& graph) {
        // Build internal data structures/state tables
        initState(graph);
        
        // Since we need to find terminal nodes (zero inedges) and nodes
        // having outedges/paths ending up on terminal nodes; this reduces
        // to finding dependency between the various graph nodes which in
        // turn requires topological sort
        // Determine the eventually safe nodes via topsort/Kahns' algo
        vector<int> safeNodesV;
        eventualSafeNodesViaTopSort(safeNodesV);
        
        // Sort the safe nodes
        sort(safeNodesV.begin(), safeNodesV.end());
        
        return safeNodesV;
    }
    
private:
    
    void
    eventualSafeNodesViaTopSort(vector<int>& safeNodesV) {
        
        // Top sort Q will contain only the eventually safe nodes
        queue<int> topSortQ;
        typedef queue<int>::size_type qSzT;
        
        // Add all terminal nodes (having zero outedges) to the topsort/bfsQ
        for (int v = 0; v != _nVertices; ++v) {
            if (0 == _nOutEdgesTbl[v]) {
                topSortQ.push(v);
            }
        }

        // Commence topsort
        while (!topSortQ.empty()) {
            // Process all nodes present in the Q at the beginning of this iteration
            int numQNodes = topSortQ.size();
            for (int i = 0; i != numQNodes; ++i) {
                // Dequeue the node/vertex from topsort Q
                auto v = topSortQ.front();
                topSortQ.pop();
                
                // Node is a terminal node OR has outedge/paths 
                // which terminate on a terminal node => eventually safe
                safeNodesV.emplace_back(v);
                
                // Remove the node 'v' from the graph. Requires removal of all edges
                // leading to 'v' from its adjacent neighbors
                auto & nbrInNodesV = _adjListTbl[v];
                for (auto & nv : nbrInNodesV) {
                    // Remove incoming edge nv->v
                    if (--_nOutEdgesTbl[nv] == 0) {
                        // Adjacent node has paths/edges leading outward => all paths
                        // from it lead to either a terminal node/eventually safe node
                        // Schedule it for top sort in the subsequent iteration
                        topSortQ.push(nv);
                    }
                }
            }
        }
    }
    
    void
    initState(vector<vector<int>>& graph) {
        // # Graph vertices
        _nVertices = graph.size();
        _nOutEdgesTbl.resize(_nVertices, 0);
        _adjListTbl.resize(_nVertices);
        
        // Iterate over the each vertex of the graph and the edges
        // Build the adjacency list and num outedges table
        for (int v = 0; v != _nVertices; ++v) {
            auto & nbrVerticesV = graph[v];
            for (auto & nv : nbrVerticesV) {
                // Edge from v -> nv
                ++_nOutEdgesTbl[v];
                _adjListTbl[nv].emplace_back(v);
            }
        }
    }
    
    // Data members
    
    // Num graph vertices
    int _nVertices;
    
    // _nOutEdgesTbl[v] => Num outgoing edges from a node 'v'
    vector<int> _nOutEdgesTbl;
    // Adjacency list representation of the graph, wherein for each node 'v',
    // an array of nodes from where incoming edges on node 'v' is maintained
    vector<vector<int> > _adjListTbl;
};
