// V => num graph vertices, E => num graph edges
// Time complexity : O(E + V)
// Space complexity : O(V)

class Solution {
public:
    bool
    isBipartite(vector<vector<int>>& graph) {
        // A graph is bipartite if each of the graph vertices can be
        // colored using 2 colors with adjacent vertices being of
        // different colors. Done via DFS or BFS
        
        _nVertices = graph.size();
        // Vertex color tristate
        // -1 uncolored, 0 white and 1 black
        _vertexColorV.resize(_nVertices, -1);
        
        //return possibleToColorGraphWith2ColorsViaBfs(graph);
        return possibleToColorGraphWith2ColorsViaDfs(graph);
    }
    
private:    
    
    bool
    possibleToColorGraphWith2ColorsViaBfs(vector<vector<int>> & graph) {
        
        // Iterate over all graph vertices
        for (int v = 0; v != _nVertices; ++v) {
            // Skip the current vertex if already colored
            if (_vertexColorV[v] != -1) {
                continue;
            }
            
            // Color the current vertex as white/0
            _vertexColorV[v] = 0;
            
            // Commence BFS from this vertex and attempt to color all the vertices
            // reachable from this vertex using 2 colors s.t no 2 adjacent vertices
            // have the same color
            queue<int> bfsQ;
            typedef queue<int>::size_type qSzT;
            bfsQ.push(v);
            while (!bfsQ.empty()) {
                
                // Visit all graph vertices at the current BFS level
                qSzT currLvlSz = bfsQ.size();
                for (qSzT i = 0; i != currLvlSz; ++i) {
                    
                    // Dequeue the vertex at Q front
                    auto dv = bfsQ.front();
                    bfsQ.pop();
                    
                    // Get color of dequeued vertex and determine the
                    // expected color of all its immediately adjacent neighbours
                    // (opposite to the dequeued vertex color)
                    int color = _vertexColorV[dv];
                    int expectedNbrColor = color ^ 1;
                    
                    // Visit all the neighbour vertices of dequeued node
                    auto & neighborVerticesV = graph[dv];
                    for (auto & nv : neighborVerticesV) {
                        if (_vertexColorV[nv] == -1) {
                            // Neigbour vertex uncolored/unvisited
                            // Color neighbour vertex with color opposite to that
                            // of dequeued node and add it to BFS queue for
                            // traversal in next iteration
                            bfsQ.push(nv);
                            _vertexColorV[nv] = expectedNbrColor;
                        } else {
                            // Neigbour vertex already colored/visited
                            if (_vertexColorV[nv] != expectedNbrColor) {
                                // Dequeued vertex and its neighbour have same color
                                // 2-coloring fails => graph is not bipartite
                                return false;
                            }
                        }
                    } // end visiting/checking all neighbour vertices
                    
                } // end of visiting all nodes at current BFS level
                
            } // end BFS
        }
        
        return true;
    }
    
    bool
    possibleToColorGraphWith2ColorsViaDfs(vector<vector<int>> & graph) {
        
        // Iterate over all graph vertices
        for (int v = 0; v != _nVertices; ++v) {
            // Skip the current vertex if already colored
            if (_vertexColorV[v] != -1) {
                continue;
            }
            
            // Color the current vertex as white/0
            _vertexColorV[v] = 0;
            
            // Commence DFS from this vertex and attempt to color
            // all the vertices reachable from this vertex using
            // 2 colors s.t adjacent vertices dont have the same color
            stack<int> dfsStk;
            typedef queue<int>::size_type qSzT;
            dfsStk.push(v);
            while (!dfsStk.empty()) {
                
                // Pop and visit the vertex at top of stack
                auto dv = dfsStk.top();
                dfsStk.pop();
                    
                // Get color of dequeued vertex and determine the
                // expected color of all its immediately adjacent neighbours
                // (opposite to the dequeued vertex color)
                int color = _vertexColorV[dv];
                int expectedNbrColor = color ^ 1;
                    
                // Visit all the neighbour vertices of dequeued node
                auto & neighborVerticesV = graph[dv];
                for (auto & nv : neighborVerticesV) {
                    if (_vertexColorV[nv] == -1) {
                        // Neigbour vertex uncolored/unvisited
                        // Color neighbour vertex with color opposite to that
                        // of dequeued node and add it to DFS stack for
                        // traversal in succeeding iterations
                        dfsStk.push(nv);
                        _vertexColorV[nv] = expectedNbrColor;
                    } else {
                        // Neigbour vertex already colored/visited
                        if (_vertexColorV[nv] != expectedNbrColor) {
                            // Dequeued vertex and its neighbour have same color
                            // 2-coloring fails => graph is not bipartite
                            return false;
                        }
                    }
                } // end visiting/checking all neighbour vertices
                
            } // end DFS
        }
        
        return true;
    }
    
private:
    
    // Data members
    // Number of graph vertices
    int _nVertices;
    // Array of vertex colors for each vertex
    vector<int> _vertexColorV;
};
