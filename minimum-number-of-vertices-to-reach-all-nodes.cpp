// V => num vertices, E => num edges
// Time complexity : O(E + V)
// Space complexity : O(V)
class Solution {
public:
    vector<int>
    findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        // We just need to find the vertices which have no 
        // incoming edges. All the vertices with incoming edges can be
        // reached from other vertices
        // Since graph is DAG, it is basically a forest of trees.
        // Only roots of all the trees need to be found to reach all vertices

        vector<bool> hasInEdgeV(n, false);
        // Iterate over all edges sequentially, marking the destination
        // vertex of all edges as having incoming edge
        for (auto & e : edges) {
            hasInEdgeV[e[1]] = true;
        }
        
        // Determine vertices with no incoming edges
        vector<int> noInEdgeVerticesV;
        for (int v = 0; v != n; ++v) {
            if (!hasInEdgeV[v]) {
                noInEdgeVerticesV.emplace_back(v);
            }
        }

        return noInEdgeVerticesV;
    }
};
