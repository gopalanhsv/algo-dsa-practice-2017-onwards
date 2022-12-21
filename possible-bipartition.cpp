class Solution {
public:
    bool
    possibleBipartition(int n, vector<vector<int>>& dislikes) {
        // Base case of lt 3 people or no dislikes
        if ((n < 3) || dislikes.empty()) {
            return true;
        }
        
        // Problem can be modelled as a graph wherein the 'n' people are the 'n'
        // graph vertices; with the dislikes forming the edges between the
        // respective vertices/people
        // Then problem reduces to a graph coloring problem wherein the entire
        // graph vertices should be colorable with a total of 2 colors, with
        // the constraint that vertices sharing an edge should not be of the
        // same color (Since we have a total of 2 groups and people(vertices) 
        // who dislike(connected via edge) should not be in same group)
        
        // Build graph
        constructGraph(n, dislikes);
        
        // Check if possible to color graph with 2 colors
        return isPossibleToColor();
    }
    
public:
    
    void
    constructGraph(int nv, vector<vector<int> >& edges) {
        _nVertices = nv;
        _adjListTbl.resize(_nVertices + 1);
        // Iterate over each edge
        for (auto & e : edges) {
            // Src/Destination vertex
            auto & sv = e[0];
            auto & dv = e[1];
            _adjListTbl[dv].emplace_back(sv);
            _adjListTbl[sv].emplace_back(dv);
        }
    }
    
    bool
    possibleToColorViaBFS(int v) {
        
        queue<int> bfsQ;
        typedef queue<int>::size_type qSzT;
        // Color the vertex 'v' and add it to BFS Q
        bfsQ.push(v);
        _colorV[v] = 0;
        
        while (!bfsQ.empty()) {
            // Iterate over all vertices in the current level
            qSzT qSz = bfsQ.size();            
            for (int i = 0; i != qSz; ++i) {
                // Dequeue the vertex at front of BFS Q
                auto cv = bfsQ.front();
                bfsQ.pop();

                auto & currVertexColor = _colorV[cv];
                
                // Visit all neighbours of current vertex and attempt to
                // color them differently from current vertex
                auto & nbrV = _adjListTbl[cv];
                for (auto & nv : nbrV) {
                    auto & nbrVertexColor = _colorV[nv];
                    if (nbrVertexColor == -1) {
                        // Nbr vertex uncolored. Assign it a color other
                        // than the current vertex color
                        nbrVertexColor = currVertexColor ^ 1;
                        // Add nbr vertex to BFS Q for coloring its neigbours
                        // in subsequent iteration
                        bfsQ.push(nv);
                    } else {
                        // Nbr vertex colored. Ensure that its color is
                        // different from that of the current vertex
                        if (nbrVertexColor == currVertexColor) {
                            // Neighbour and current vertex have same color
                            // => coloring not feasible
                            return false;
                        }
                    }
                }
            }
        }
            
        // Possible to color the connected component of 'v' with 2 colors
        return true;
    }
    
    bool
    possibleToColorViaDFS(int v, int vertexColor) {
        
        // Color the vertex 'v' with given color
        _colorV[v] = vertexColor;
        
        // Visit all neighbours of current vertex
        auto & nbrV = _adjListTbl[v];
        for (auto & nv : nbrV) {

            if (_colorV[nv] == vertexColor) {
                // Neighbour and current vertex have same color
                // => coloring not feasible
                return false;
            }
            
            // Nbr vertex uncolored. Assign it a color other
            // than the current vertex color
            if ((_colorV[nv] == -1) &&
                !possibleToColorViaDFS(nv, vertexColor ^ 1)) {
                return false;
            }
        }
            
        // Possible to color the connected component of 'v' with 2 colors
        return true;
    }
    
    #define DFS
    bool
    isPossibleToColor() {
        // All vertices uncolored (-1) initially
        _colorV.resize(_nVertices + 1, -1);
        
        // Iterate over each vertex and attempt to color the
        // reachable edges greedily via BFS with 2 colors (0/1)
        for (int v = 1; v <= _nVertices; ++v) {
            if (-1 == _colorV[v]) {
                // vertex 'v' not colored. Attempt the color the
                // entire connected component in which 'v' is
                // present in 2 colors as per constraints
                #ifdef BFS
                if (!possibleToColorViaBFS(v)) {
                    // Coloring fails
                    return false;
                }
                #endif
                #ifdef DFS
                if (!possibleToColorViaDFS(v, 0)) {
                    // Coloring fails
                    return false;
                }
                #endif
            }
        }
        
        // Possible to color the graph in 2 colors
        return true;
    }
    
    // Data members
    int _nVertices;
    vector<vector<int> > _adjListTbl;
    vector<int> _colorV;
};
