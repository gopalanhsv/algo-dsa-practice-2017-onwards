// V => Num vertices, E => Num edges
// Time complexity : O(E) + O(V ^ 3)
// Space complexity : O(V ^ 2)

// Adjacency matrix implementation results in massive perf increase ove adjacency list

class Solution {
public:
    int
    minTrioDegree(int n, vector<vector<int>>& edges) {
        // Table maintaining degree of each vertex
        vector<int> degreeTbl(n, 0);
        // Adjacency matrix representation of graph to check for pre-existing edges
        // (matrix preferred for perf reasons)
        vector<vector<bool> > adjMatrixTbl(n, vector<bool>(n, false));
        // Iterate over each edge
        for (auto & edge : edges) {
            auto u = edge[0] - 1;
            auto v = edge[1] - 1;
            // Populate the degree table for edge vertices
            degreeTbl[u]++;
            degreeTbl[v]++;
            // Populate the adjacency matrix
            adjMatrixTbl[u][v] = true;
            adjMatrixTbl[v][u] = true;
        }
        
        // Since there are no repeated/parallel edges, the 3 edges connecting
        // the 3 vertices forming a trio contribute value of +2 to each vertex 
        // degree (2 different edges to the 2 other trio members from each trio
        // member).
        // Degree of a connected trio being the number of edges going out of the
        // trio would then be the sum of teh degrees of the trio members minus
        // the contribution of internal edges (between members) to the degree
        // i.e. If u, v, w form a connected trio,
        // then degree of (u, v, w) = degree(u) + degree(v) + degree(w) - 6
        
        // Determine all the connected trios in the graph
        auto minTrioDegree = numeric_limits<int>::max();
        
        // Iterate over each possible exclusive triplets of graph vertices
        for (auto u = 0; u < n; ++u) {
            for (auto v = u + 1; v < n; ++v) {
                if (adjMatrixTbl[u][v]) {
                    // (u, v) form an edge
                    for (auto w = v + 1; w < n; ++w) {
                        if (adjMatrixTbl[u][w] && adjMatrixTbl[v][w]) {
                            // (u, w) & (v, w) also form edges
                            // => (u, v, w) are interconnected and form a trio
                            
                            // Compute degree of connected trio (u, v, w)
                            auto currentTrioDegree = 
                                degreeTbl[u] + degreeTbl[v] + degreeTbl[w] - 6;
                            minTrioDegree = min(minTrioDegree, currentTrioDegree);
                        }
                    }
                }
            }
        }
    
        return (numeric_limits<int>::max() == minTrioDegree) ? -1 : minTrioDegree;
    }
};
