// V => Num vertices, E => Num edges
// Time complexity : O(E) + O(V)
// Space complexity : O(E + V)
class Solution {
public:
    bool
    isPossible(int n, vector<vector<int>>& edges) {
        
        // Table maintaining degree of each vertex
        vector<int> degreeTbl(n, 0);
        // Adjacency matrix representation of the graph
        // Adjacency list representation of graph to check for pre-existing edges
        // (not possible to use adjacency matrix due to memory constraints)
        vector<unordered_set<int> > adjacencyTbl(n);
        // Iterate over each edge
        for (auto & edge : edges) {
            auto u = edge[0] - 1;
            auto v = edge[1] - 1;
            // Populate the degree table for edge vertices
            degreeTbl[u]++;
            degreeTbl[v]++;
            // Populate the adjacency table
            adjacencyTbl[u].insert(v);
            adjacencyTbl[v].insert(u);
        }
        
        // As self loops as not allowed, adding a new edge increments the degree
        // of the different edge vertices by 1 => new edge(s) should be added only
        // between vertices of odd degree in order to make it even, and not between
        // even degree'd vertices
        // Since at most 2 additional edges may be added to make all vertices of even
        // degree; from the aforementioned we have following 3 cases of edge addition
        // Case 1. 0 edges added
        // Case 1. 1/2 new edges added
        // Case 2. 2 edges added
        
        // Determine the odd degree'd vertices
        vector<int> oddDegVerticesV;
        for (auto v = 0; v != n; ++v) {
            if (degreeTbl[v] % 2 != 0) {
                oddDegVerticesV.emplace_back(v);
            }
        }

        auto nOddDegVtx = oddDegVerticesV.size();
        // Case 2
        if (2 == nOddDegVtx) {
            // Graph has 2 odd degree vertices
            auto u = oddDegVerticesV[0];
            auto v = oddDegVerticesV[1];
            // Either 1 new edge should be possible between u & v OR
            // 2 new edges between u & x, v & x; where x is even degree vertex
            for (auto x = 0; x < n; ++x) {
                if (!adjacencyTbl[u].count(x) && !adjacencyTbl[v].count(x)) {
                    // Possible to add either 1 edge between u & v OR
                    // 2 edges between u & x, v & x
                    // Condition !adjacencyTbl[u].count(u) && !adjacencyTbl[u].count(v)
                    // takes care of single edge addtion check
                    return true;
                }
            }
        }
        // Case 3
        if (4 == nOddDegVtx) {
            // Graph has 4 odd degree vertices
            auto u = oddDegVerticesV[0];
            auto v = oddDegVerticesV[1];
            auto p = oddDegVerticesV[2];
            auto q = oddDegVerticesV[3];
            
            if ((!adjacencyTbl[u].count(v) && !adjacencyTbl[p].count(q)) ||
                (!adjacencyTbl[u].count(p) && !adjacencyTbl[v].count(q)) ||
                (!adjacencyTbl[u].count(q) && !adjacencyTbl[p].count(v)) ) {
                // No pre-existing edges between the 2 disjoint sets of 2 odd degree vertices each
                // => 2 new edges can be added
                return true;
            }
        }
        
        // Case 1
        return (0 == nOddDegVtx);
    }
};
