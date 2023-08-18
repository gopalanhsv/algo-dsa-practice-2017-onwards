// n => Num cities
// Time complexity : O(n^2)
// Space complexity : O(n^2)
class Solution {
public:
    int
    maximalNetworkRank(int n, vector<vector<int>>& roads) {
        // Problem is modelled as a graph wherein each city is a vertex
        // and the roads between cities are the graph edges. 
        // Maintain the degree of each vertex/city as this gives the number of
        // directly connected roads/edges to the particular city (as there are
        // no self loops)
        
        // Since there are no multiple edges between a vertex pair (at most one road
        // connecting the pair as per input constraints); the network rank of the
        // pair of cities would be the sum of the degrees of the respective endpoint
        // cities minus the number of direct edges connecting the pair (only if there
        // is a direct edge between the cities to account for the edge being counted twice)
        
        // Table maintaining degree of each city
        vector<int> degreeTbl(n, 0);
        // Adjacency matrix representation of the road network graph between cities
        // Using adj matrix instead of adj list as it allows for fast check of
        // existence of a road/edge between two cities
        vector<vector<bool> > adjacenyMatrix(n, vector<bool>(n, false));
        // Iterate over each road/edge
        for (auto & road : roads) {
            auto & u = road[0];
            auto & v = road[1];
            // Build the degree table for the city pair at road extremities
            degreeTbl[u]++;
            degreeTbl[v]++;
            // Populate the adjacency matrix
            adjacenyMatrix[u][v] = true;
            adjacenyMatrix[v][u] = true;
        }
        
        auto maxNetworkRank = 0;
        // Iterate over each possible valid city pair (excluding self city pairs)
        for (auto u = 0; u < n; ++u) {
            for (auto v = u + 1; v < n; ++v) {
                // Determine the network rank between city pair u & v
                auto networkRank = degreeTbl[u] + degreeTbl[v];
                if (adjacenyMatrix[u][v]) {
                    // Account for double couting of the direct edge between current city pair
                    networkRank--;
                }
                // Update the maximum network rank
                maxNetworkRank = max(maxNetworkRank, networkRank);
            }
        }
        
        return maxNetworkRank;
    }
};
