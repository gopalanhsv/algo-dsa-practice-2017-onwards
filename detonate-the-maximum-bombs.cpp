// n => bombs.size()
// Num graph vertices => n, num graph edges => n x n
// Time complexity : O(V) x O(V + E) => O(n x n x n)
// Space complexity : O(V + E) + O(V) => O(V + E) => O(n x n)

class Solution {
public:
    int
    maximumDetonation(vector<vector<int>>& bombs) {
        // Problem is modelled as follows :-
        // The bomb locations are graph vertices
        // Two bombs are connected by an edge if both the bombs are in detonation
        // range (i.e one bomb x detonating the other y implies an edge from x -> y)
        // Exec a BFS/DFS from a vertex (bomb) and visit all reachable vertices
        // tracking count of visited vertices in this iteration. This will be the group
        // of bombs which are within each other detination range and one 
        // explosion leads to dentonation of all others.
        // Repeat the BFS till all vertices are visited keeping track
        // of the max number of bombs visited in each BFS bomb group visit
        
        // Create graph
        initGraph(bombs);
        
        // Iterate over all vertices/bombs
        int maxBombsDetonated = 0;
        for (int v = 0; v != _nVertices; ++v) {
            // Detonate bomb 'v' and all those in synchronous range via BFS.
            // Track the number of visited/detonated bombs
            int nVisitedBombs = bfs(v);
            maxBombsDetonated = max(maxBombsDetonated, nVisitedBombs);
        }
        
        return maxBombsDetonated;
    }
    
private:
    
    void
    initGraph(vector<vector<int>>& bombs) {
        // Bombs are graph/DAG vertices
        _nVertices = bombs.size();
        // Iterate over all possible bomb pairs
        for (int i = 0; i != _nVertices; ++i) {
            auto & xi = bombs[i][0];
            auto & yi = bombs[i][1];
            auto & ri = bombs[i][2];
            long long ri2 = (long long)ri * ri;
            for (int j = 0; j != _nVertices; ++j) {
                
                if (j == i) {
                    continue;
                }
                
                // Check if bomb 'j' lies in detonation range of bomb 'i' 
                // i.e bomb 'i' detonates bomb 'j'
                auto & xj = bombs[j][0];
                auto & yj = bombs[j][1];
                long long dx = xi - xj;
                long long dy = yi - yj;
                // Bomb 'j' is in range of bomb 'i' if distance between their
                // centers is less that the radius of bomb 'i'. So bomb 'i'
                // detonation leads to bomb 'j' detonation and hence a 
                // DAG directed edge from i -> j;
                if ((dx * dx + dy * dy) <= ri2) {
                    // Edge between bomb vertices 'i' to 'j' representing
                    // 'i' dentonation impacts 'j'
                    _adjList[i].emplace_back(j);
                }
            }
        }
    }
    
    int
    bfs(int startVertex) {
        // All vertices marked unvisted
        vector<bool> visitedV(_nVertices, false);
        // Enqueue start vertex to BFS Q and mark as visited
        queue<int> bfsQ;
        typedef queue<int>::size_type qSzT;
        bfsQ.push(startVertex);
        visitedV[startVertex] = true;
        int nVisited = 0;
        
        // Commence BFS
        while (!bfsQ.empty()) {
            qSzT currLvlSz = bfsQ.size();
            // Iterate over all vertices at current BFS level
            for (qSzT i = 0; i != currLvlSz; ++i) {
                // Dequeue the vertex at queue front
                auto v = bfsQ.front();
                bfsQ.pop();
                // Visit dequeued vertex
                ++nVisited;
                
                // Iterate over all neighbors of dequeued vertex
                // and set up the unvisited ones for a BFS visit
                // at the next level
                auto & nbrsV = _adjList[v];
                for (auto & nv : nbrsV) {
                    if (!visitedV[nv]) {
                        bfsQ.push(nv);
                        visitedV[nv] = true;
                    }
                }
            }
        }
        
        return nVisited;
    }
    
    // Data members
    // Graph adjacency list
    unordered_map<int, vector<int> > _adjList;
    // Num vertices
    int _nVertices;
};
