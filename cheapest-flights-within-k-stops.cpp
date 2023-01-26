class Solution {
public:
    int
    findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Problem is modelled as a directed graph wherein the cities are the vertices,
        // flights are the directed graph edges and flight price being the edge weight
        // The problem then reduces to finding the shortest cost path from source to
        // destination with at most 'k' intermediate stops/or 'k + 1' edges
        // The above can be done via either BFS, Bellman Ford or Dijkstra
        
        // Construct graph (adjacency list) from the flight 
        buildGraph(n, flights);
        
        // Compute shortest path cost from source to destination city
        return shortestPathCostBFS(n, src, dst, k);
        //return shortestPathCostBellmanFord(n, src, dst, k);
        //return shortestPathCostDijkstra(n, src, dst, k);
    }
    
private:
    
    void
    buildGraph(int n, vector<vector<int>>& flights) {
        _adjListTbl.resize(n);
        // Iterate over each flight
        for (auto & flight : flights) {
            // Src, dest & price
            auto & s = flight[0];
            auto & d = flight[1];
            auto & cost = flight[2];
            // Add flight details as an edge to the graph
            _adjListTbl[s].emplace_back(pair<int, int>(d, cost));
        }
    }
    
    int
    shortestPathCostBFS(int n, int src, int dst, int k) {
        // Tracks the most recent updated min cost to
        // of the vertices from the source vertex
        vector<int> minPathCostTbl(n, numeric_limits<int>::max());
        
        // Track the number of intermediate stops/vertices seen so far on
        // the various radial path commencing from the source vertex
        int nStopsSeen = -1;
        // BFS Q holding tuples of {vertex, minpath cost to vertex from source}
        queue<pair<int, int> > bfsQ;
        typedef queue<pair<int, int> >::size_type qSzT;
        
        // Commence BFS from the source vertex
        minPathCostTbl[src] = 0;
        bfsQ.push({src, minPathCostTbl[src]});
        // BFS traversal till 'k' stops/'k + 1' edges after source
        // are visited OR reachable nodes get fully explored 
        while (!bfsQ.empty()) {
            // Visit all the nodes at a hop count of 'nStopsSeen' from source
            // i.e. at the current level
            qSzT currLvlSz = bfsQ.size();
            for (qSzT i = 0; i != currLvlSz; ++i) {
                // Dequeue and visit the vertex at front of BFS Q
                auto & vtxPathInfo = bfsQ.front();
                auto v = vtxPathInfo.first;
                auto pathCost = vtxPathInfo.second;
                bfsQ.pop();
                
                // Iterate over all the adjacent reachable neighbours
                // of current vertex 
                auto & nbrInfoV = _adjListTbl[v];
                for (auto & [nbr, edgeCost] : nbrInfoV) {
                    // Compute cost reaching neighbor from source via current vertex
                    auto pathCostToNbr = pathCost + edgeCost;
                    if (pathCostToNbr < minPathCostTbl[nbr]) {
                        // Path from source to neighbor via current vertex is
                        // shorter than the paths seen so far. Update path cost
                        // for neighbor and add the neighbor to be explored in
                        // next BFS iteration
                        minPathCostTbl[nbr] = pathCostToNbr;
                        bfsQ.push({nbr, pathCostToNbr});
                    }
                }
            }
            
            if (++nStopsSeen == k) {
                // Explored all reachable vertices at mode 'k+1' edges
                // away from source(i.e. with 'k' intermediate stops)
                break;
            }
        }
        
        return
            (minPathCostTbl[dst] == numeric_limits<int>::max()) ? -1 : minPathCostTbl[dst];
    }
    
    
    // Data members
    
    // Graph representation of cities and flights
    // Each city is mapped to a list of tuple/pairs of {flight destination, flight price}
    // originating from the particular city
    vector<vector<pair<int, int> > > _adjListTbl;
};
