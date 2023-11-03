// e => times.size()/ # edges
// n => # vertices
// Time complexity : O(n + elogn)
// Space complexity : O(n + e)

class Solution {

public:
    int
    networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // Create network graph
        buildNetworkGraph(times);
        // Commence a Dijkstra from given node 'k' in order
        // to visit all graph nodes
        int timeToVisitAllNodes = doSpf(k, n);
        return timeToVisitAllNodes;
    }
    
private:
    
    void
    buildNetworkGraph(vector<vector<int> >& times) {
        // Travel times form the graph edges. 
        // Iterate over the times and build the network graph adjacency list
        for (auto & e : times) {
            auto & s = e[0]; // source node
            auto & d = e[1]; // destination node
            auto & c = e[2]; // cost/travel time
            _adjList[s].emplace_back(pair<int, int>(d, c));
        }
    }
    
    int
    doSpf(int src, int nNodes) {
    
        typedef pair<int, int> NodeTravelTimeTupleT;
        struct NodeTravelTimeTupleObjCmp {
            bool
            operator()(const NodeTravelTimeTupleT& p1, const NodeTravelTimeTupleT& p2) {
                return p1.second > p2.second;
            }
        };
        
        priority_queue<NodeTravelTimeTupleT, vector<NodeTravelTimeTupleT>, NodeTravelTimeTupleObjCmp> reachableNodesPQ;
        
        vector<int> travelTimeV(nNodes + 1, numeric_limits<int>::max());
        
        reachableNodesPQ.push({src, 0});
        int nReachableNodes = 0;    
        int totalDelay = 0;
        while (!reachableNodesPQ.empty()) {
            auto &nodeTravelTimeP = reachableNodesPQ.top();
            auto v = nodeTravelTimeP.first;
            auto currNodeTravelTime = nodeTravelTimeP.second;
            reachableNodesPQ.pop();
            if (travelTimeV[v] == numeric_limits<int>::max()) {
                ++nReachableNodes;
            }
            if (currNodeTravelTime >= travelTimeV[v]) {
                continue;
            }
            travelTimeV[v] = min(travelTimeV[v], currNodeTravelTime);
            totalDelay = max(totalDelay, travelTimeV[v]);
            
            auto & nbrCostsV = _adjList[v];
            for (auto & nbrCostP : nbrCostsV) {
                auto & nv = nbrCostP.first;
                auto & travelTime = nbrCostP.second;
                auto timeToReachNbrViaCurrentNode = 
                    currNodeTravelTime + travelTime;
                if (timeToReachNbrViaCurrentNode < travelTimeV[nv]) {
                    
                    reachableNodesPQ.push({nv, timeToReachNbrViaCurrentNode});
                }
            }
        }
        
        return nNodes == nReachableNodes ? totalDelay : -1;
    }
    
    // Data members
    // Adjacency list representing the network graph mapping from a
    // source node to list of neighbour node/cost to neighbour node tuples
    unordered_map<int, vector<pair<int, int> > > _adjList;
};
