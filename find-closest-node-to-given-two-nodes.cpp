class Solution {
public:
    int
    closestMeetingNode(vector<int>& edges, int node1, int node2) {
        
        // Compute the min distance from 'node1' and 'node2' to each
        // of the nodes via BFS/DFS. BFS/DFS can be used without the
        // queue/stack as there is at most only a single outedge from
        // each node (i.e. only a single reachable neighbor at most)
        _nNodes = edges.size();
        
        // Init the distances from both of 'node1' and 'node2' to '+infinity'
        _distV.resize(2, vector<int>(_nNodes, numeric_limits<int>::max()));
        
        // Compute shortest distance from 'node1' to each of the reachable nodes
        distanceViaDFS(edges, node1, 0);
        // Compute shortest distance from 'node2' to each of the reachable nodes 
        distanceViaDFS(edges, node2, 1);
        
        // Determine the node with smallest index with min-value of
        // max of distances from either node1 or node2
        int minOfMaxDist = numeric_limits<int>::max();
        int minOfMaxDistVertex = -1;
        // Iterate over each node
        for (int v = 0; v != _nNodes; ++v) {
            // Skip nodes which are unreachable from either of node1/2
            if ((_distV[0][v] != numeric_limits<int>::max()) &&
                (_distV[1][v] != numeric_limits<int>::max())) {
                // Node 'v' is reachable from both 'node1' and 'node2'
                // Take the max of distance from node1/2
                int maxDist = max(_distV[0][v], _distV[1][v]);
                if (maxDist < minOfMaxDist) {
                    // Node 'v' is reachable with a smaller distance
                    minOfMaxDist = maxDist;
                    minOfMaxDistVertex = v;
                }
            }
        }
        
        return minOfMaxDistVertex;
    }
    
private:
    
    void
    distanceViaDFS(vector<int>& edges, int source, int srcIdx) {
        
        // No need for a stack as there a max of one outedge per vertex
        vector<bool> visitedV(_nNodes, false);
        int distFromSrc = 0;
        // Commence DFS from the source node
        int nodeToBeVisited = source;
        // Keep visiting unvisited vertices till a dead-end is hit (i.e
        // a vertex with no outedge)
        while ((nodeToBeVisited != -1) && !visitedV[nodeToBeVisited]) {
            // Mark the current node being visited
            auto v = nodeToBeVisited;
            visitedV[v] = true;
            
            // Update the max distance from the source(s) for visited vertex
            _distV[srcIdx][v] = distFromSrc;
            
            // Sole outedge from current node is next node to be visited
            nodeToBeVisited = edges[v];
            
            // Increment distance from source node for next iteration
            ++distFromSrc;
        }
    }
    
    // Data members
    
    // Number of nodes
    int _nNodes;
    // Array holding distances to each graph node from the
    // 2 nodes 'node1' and 'node2' respectively
    vector<vector<int> > _distV;
};
