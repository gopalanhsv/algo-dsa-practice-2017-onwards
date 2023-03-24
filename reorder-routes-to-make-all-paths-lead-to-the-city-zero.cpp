// Time Complexity
//  O(num vertices) => O(num cities)
// Space Complexity
// O(num vertices + num edges) => O(num cities + num connections)

class Solution {
public:
    typedef struct _NbrInfoT {
        // Adjacent Neighbor vertex id
        int nbr;
        // True if neighbor 'nbr' reachable by forward edge,
        // False if reachable via backward edge
        bool fwdEdge;
    } NbrInfoT;

    int
    minReorder(int nCities, vector<vector<int>>& connections) {
        
        // 
        
        // Build the graph representing the road network
        constructRoadNetworkGraph(connections);
        
        //return minReorderBFS(nCities);
        return minReorderDFS(nCities);
    }
    
private:

    void
    constructRoadNetworkGraph(vector<vector<int>>& edges) { 
        // Iterate over each of the edges/roads connecting the cities and add the
        // roads to the adjacency list representation of the road network
        for (auto & e : edges) {
            // Src and destination city for current road/edge
            auto & src = e[0];
            auto & dst = e[1];
            
            // Forward road/edge - in same direction as the current road/edge direction
            NbrInfoT nbrInfo;
            nbrInfo.nbr = dst;
            nbrInfo.fwdEdge = true;
            _adjListTbl[src].emplace_back(nbrInfo);
            // Backward road/edge - in opposite direction to the current road/edge direction
            nbrInfo.nbr = src;
            nbrInfo.fwdEdge = false;
            _adjListTbl[dst].emplace_back(nbrInfo);
        }
    }
    
    int
    minReorderBFS(int nVertices) {
        
        int nForwardEdges = 0;
        queue<int> bfsQ;
        typedef queue<int>::size_type qSzT;
        vector<bool> visitedV(nVertices, false);
        
        // Commence BFS from vertex 0
        bfsQ.push(0);
        visitedV[0] = true;
        while (!bfsQ.empty()) {
            qSzT currLvlSz = bfsQ.size();
            for (int i = 0; i != currLvlSz; ++i) {
                auto v = bfsQ.front();
                bfsQ.pop();
                
                auto & nbrInfoV = _adjListTbl[v];
                for (auto & nbrInfo : nbrInfoV) {
                    auto & nv = nbrInfo.nbr;
                    if (!visitedV[nv]) {
                        visitedV[nv] = true;
                        bfsQ.push(nv);
                        if (nbrInfo.fwdEdge) {
                            ++nForwardEdges;
                        }
                    }
                }
            }
        }
        
        return nForwardEdges;
    }
    
    int
    minReorderDFS(int nVertices) {
        
        int nForwardEdges = 0;
        stack<int> dfsStk;
        vector<bool> visitedV(nVertices, false);
        
        // Commence DFS from vertex 0
        dfsStk.push(0);
        visitedV[0] = true;
        while (!dfsStk.empty()) {
            
            auto v = dfsStk.top();
            dfsStk.pop();
            
            auto & nbrInfoV = _adjListTbl[v];
            for (auto & nbrInfo : nbrInfoV) {
                auto & nv = nbrInfo.nbr;
                if (!visitedV[nv]) {
                    visitedV[nv] = true;
                    dfsStk.push(nv);
                    if (nbrInfo.fwdEdge) {
                        ++nForwardEdges;
                    }
                }
            }
        }
        
        return nForwardEdges;
    }
    
    // Data members
    unordered_map<int, vector<NbrInfoT> > _adjListTbl;
};
