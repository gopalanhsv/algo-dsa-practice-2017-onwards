// E => num edges, V => n/num vertices
// A => num calls to add edge
// S => num calls to shortest path

// Dijkstra
// Time complexity : O(E + V + A + S(V + ElogV))
// Space complexity : O(E + V + A)

class Graph {
public:
    Graph(int n, vector<vector<int>>& edges) {
        _nVertices = n;
        // Initialize graph with the given edges
        _adjListTbl.resize(n);
        for (auto & edge : edges) {
            addEdge(edge);
        }
    }
    
    void
    addEdge(vector<int> edge) {
        // Edge vertices & cost
        auto & u = edge[0];
        auto & v = edge[1];
        auto & cost = edge[2];
        // Add edge (u, v) to adjacency list table
        _adjListTbl[u].push_back({v, cost});
    }
    
    int
    shortestPath(int node1, int node2) {
        // Exec SPF (Dijkstra) from 'node1' to find the min cost path
        // length to 'node2'
        
        typedef pair<int, int> NodePathLenTupleT;
        struct NodePathLenTupleCmpObj {
            bool
            operator()(const NodePathLenTupleT& p1, const NodePathLenTupleT& p2) {
                return p1.second > p2.second;
            }
        };
        // PQ/min heap of (node, node path len from node1) tuples of nodes reachable from 'node1'
        // organized in PQ with nodes closer to 'node1' arranged near to PQ top  compared
        // with nodes farther away from 'node1'
        priority_queue<NodePathLenTupleT, vector<NodePathLenTupleT>, NodePathLenTupleCmpObj>
            reachableNodesQ;

        // spLenV[x] is the min cost path len to vertex 'x' from vertex 'node1'
        // Initialized to +infinity
        vector<int> spLenV(_nVertices, numeric_limits<int>::max());

        // Commence SPF/Dijkstra from 'node1'
        reachableNodesQ.push({node1, 0});
        //spLenV[node1] = 0;

        while (!reachableNodesQ.empty()) {
            auto & nodePathLenP = reachableNodesQ.top();
            // Node 'v' reachable from 'node1' with path len 'pathLen'
            auto v = nodePathLenP.first;
            auto pathLen = nodePathLenP.second;
            reachableNodesQ.pop();

            if (pathLen >= spLenV[v]) {
                // Node 'v' already reachable from 'node1' via shorter path
                // Ignore current path
                continue;
            }
            
            // Node 'v' reachable via a lower cost path from 'node1'. Update
            // shortest path len and add node 'v' neighbors to PQ
            spLenV[v] = pathLen;
            
            if (v == node2) {
                // Reached destination
                return pathLen;
            }
            
            // Add all neighbors of 'nv' which can be reached via a shorter
            // path from node 'node1' via current node 'v' to the PQ for
            // processing
            auto & nbrCostTuplesV = _adjListTbl[v];
            // Iterate over each neighbor of/edge emanating from 'v' 
            for (auto & nbrCostTuple : nbrCostTuplesV) {
                // Neighbor vertex 'nv' & its edge cost
                auto & nv = nbrCostTuple.first;
                auto & edgeCost = nbrCostTuple.second;
                // Path len of path form 'node1' to 'nv' via 'v'
                auto nbrPathLen = edgeCost + pathLen;
                if (nbrPathLen < spLenV[nv]) {
                    // Node 'nv' reachable via a lower cost path from 'node1'
                    // Schedule node 'nv' for Dijkstra processing 
                    reachableNodesQ.push({nv, nbrPathLen});
                }
            }
        }
        
        // No path to node2 from node1
        return -1;
    }
    
protected:
    
    // Data members
    // Table mapping each node to an array of <neighbor node, edge cost to neighbor node>
    // tuples for each node/edge in the graph
    vector<vector<pair<int, int> > > _adjListTbl;
    // Num graph vertices
    int _nVertices;
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */
