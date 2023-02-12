class Solution {
public:
    long long
    minimumFuelCost(vector<vector<int>>& roads, int seats) {
        // Build the road network graph (tree) 
        buildRoadNetworkGraph(roads);

        // Postorder DFS is done commencing from capital city '0'
        // to determine the number of representatives coming to each
        // city from the subtree rooted at a city; which is used to
        // compute the min number of cars (and hence the min fuel) reqd
        // to transport the subtree representatives towards the subtree
        // root parent on the way to the capital/root node 
        minFuelCostFromSubtreeRoot(0, -1, seats);

        return _minFuelCost;
    }
    
private:
    
    void
    buildRoadNetworkGraph(vector<vector<int>>& roads) {
        // Since the road network is a fully connected graph with no
        // cycles, the number of cities(vertices) is 1 more than the
        // number of roads(edges)
        int nCities = roads.size() + 1;
        _graphTbl.resize(nCities);
        // Iterate over each road and build the adjacency table
        // representation of the graph
        for (auto & road : roads) {
            auto & u = road[0];
            auto & v = road[1];
            _graphTbl[u].emplace_back(v);
            _graphTbl[v].emplace_back(u);
        }
    }
    
    long long
    minFuelCostFromSubtreeRoot(int currNode, int parentNode, int seats) {
         
        // Subtree size of tree rooted at current node (initialized
        // to 1 - current node)
        // This would be the total number of representatives which go
        // from current city towards the capital via the parent node
        long long nSubtreeSz = 1;
        // Iterate over each neighbor of the current node
        auto & nbrV = _graphTbl[currNode];
        for (auto & nv : nbrV) {
            // Skip the edge towards parent node (towards root)
            if (nv != parentNode) {
                // Determine the number of representatives in the subtree
                // rooted at 'nv' and the fuel cost for them to reach
                // current node from 'nv'
                nSubtreeSz +=
                    minFuelCostFromSubtreeRoot(nv, currNode, seats);
            }
        }
        
        // Compute minimum cars required for representatives of cities in the
        // subtree nodes rooted at/hanging off the subtree  rooted at current
        // node to reach the current node parent. Number of representatives
        // travelling in cars between current node and its parent would be
        // those who represent the cities in the subtree rooted at current node
        // i.e. identical to  the number of cities in current nodes' subtree
        // (since each city has a single representative)
        long long nCars = nSubtreeSz / seats;
        if (nSubtreeSz % seats != 0) {
            ++nCars;
        }
        
        // Number of cars for ferrying representatives from current node to
        // its parent would be the min fuel cost for the same function.
        // Add this cost to the total minimum fuel cost required
        if (-1 != parentNode) {
            _minFuelCost += nCars;
        }
            
        return nSubtreeSz;
    }
    
    // Data members
    // Road network adjacency list representation
    vector<vector<int> > _graphTbl;
    
    // Tracks the total min fuel cost for ferrying representatives from
    // various cities to the capital '0' up the tree
    long long _minFuelCost = 0;
};
