// n => routes.size(), M => max(routes.size())/max bus stops on route
// Time complexity : O(M(n^2))
// Space complexity : O(nM)

class Solution {
public:
    int
    numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        return numBusesToDestinationViaBFS(routes, source, target);
    }
    
private:
    
    int
    numBusesToDestinationViaBFS(vector<vector<int>>& routes, int source, int target) {
        
        // Problem space is modeled as a directed graph wherein the routes are the graph
        // vertices; with directed edges between the sequential bus stops along a particular
        // route. Each edge is also tagged with the route id to determine bus changes
        // Problem reduces to doing a BFS traversal from 'source' to 'target' bus
        // stop; tracking the number of buses/tags seen along the way. The number buses/tags
        // seen till the 'target' is reached will be the least number of buses/route required
        // for travel - as BFS does the shortest path routing for same edge weights

        if (source == target) {
            // Base case of same source and destination => no bus reqd
            return 0;
        }
        
        // Construct the bus route graph
        buildGraph(routes);

        // Do a BFS traversal from 'source' to 'target' tracking the number of seen buses
        // Traversal info tracking the BFS bus traversal across the bus route graph

        // Bus routes to which source & target bus stop respectively belong
        auto & srcRoutes = _stopIdToRoutesTbl[source];
        auto & dstRoutes = _stopIdToRoutesTbl[target];

        queue<int> bfsQ;
        unordered_set<int> visitedRoutesTbl;
        // Add each of the routes passing through source bus stop to BFS Q
        for (auto & srcRt : srcRoutes) {
            bfsQ.push(srcRt);
            visitedRoutesTbl.insert(srcRt);
        }

        // Commence BFS
        auto nLevels = 1;
        while (!bfsQ.empty()) {
            auto currLvlSz = bfsQ.size();
            // Visit all the vertices/routes at the current level
            for (auto i = 0; i != currLvlSz; ++i) {
                // Dequeue vertex/route at front of BFS Q and visit it
                auto v = bfsQ.front();
                bfsQ.pop();

                if (dstRoutes.find(v) != dstRoutes.end()) {
                    // Reached target/destination bus route
                    return nLevels;
                }

                // Schedule all the unvisited directly reachable routes from the bus
                // stops on the current route for a BFS traversal in the next iteration
                auto & busStopsV = routes[v];
                // Iterate over each of the bus stops serviced by the current bus route
                for (auto & busStop : busStopsV) {
                    // Iterate over each of the bus routes touching this bus stop
                    for (auto & reachableRtId : _stopIdToRoutesTbl[busStop]) {
                        // Skip visited bus routes and process only the new unvisited ones
                        if (visitedRoutesTbl.find(reachableRtId) == visitedRoutesTbl.end()) {
                            // Mark neighbour route as visited
                            visitedRoutesTbl.insert(reachableRtId);
                            // Schedule neighbour route for a BFS visit in subsequent iteration
                            bfsQ.push(reachableRtId);
                        }
                    }
                }
            }

            ++nLevels;
        }

        // Not able to reach 'target' along specified routes
        return -1;
    }

    void
    buildGraph(vector<vector<int>>& routes) {
        // Build a mapping from each bus stop id to the set of routes 
        // which pass through the bus stop
        int nRoutes = routes.size();
        for (int rtId = 0; rtId != nRoutes; ++rtId) {
            auto & busStopsV = routes[rtId];
            for (auto & busStop : busStopsV) {
                _stopIdToRoutesTbl[busStop].insert(rtId);
            }
        }
    }

    
    // Data members
    // Bus route graph
    
    // Mapping from each bus stop id to the set of routes which pass through the bus stop
    unordered_map<int, unordered_set<int> > _stopIdToRoutesTbl;
};
