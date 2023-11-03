// Time complexity : O(n ^ 3)
// Space complexity : O(n ^ 2)

class Solution {
public:
    int
    findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Problem is modelled as a weighted graph with cities being the vertices
        // and edges being the direct connections between cities with the resp weights
        // Problems reduces to finding the shortest path length between all pairs of
        // cities; processing all the shortest path length info to determine cities from
        // which other cities are reachable within the specified distance threshold
        
        // Find shortest path between all pairs of cities via Floyd Warshall
        // as all edges have +ve weights => no -ve cycles
        
        // Init SP lengths between all city pairs to +inf
        vector<vector<long long> > spLenTbl(n, vector<long long>(n , numeric_limits<int>::max()));
        // Iterate over each edge and init single hop path len between cities
        for (auto & e : edges) {
            auto & u = e[0];
            auto & v = e[1];
            auto & wt = e[2];
            spLenTbl[u][v] = wt;
            spLenTbl[v][u] = wt;
        }
        // Path len between identical src/dst pairs is 0
        for (auto v = 0; v < n; ++v) {
            spLenTbl[v][v] = 0;
        }

        // Floyd Warshall
        // Iterate over each possible intermediate city 
        for (auto k = 0; k < n; ++k) {
            // Iterate over all possible source/destination city pairs
            for (auto s = 0; s < n; ++s) { // Source city
                for (auto d = 0; d < n; ++d) { // Destination
                    // Compute the min distance from s->d via city 'k'
                    long long minSrcDstDistViaK = spLenTbl[s][k] + spLenTbl[k][d];
                    if (minSrcDstDistViaK < spLenTbl[s][d]) {
                        // Path from s->d via city 'k' is shorter
                        // Update the SP len from s->d to be via city 'k'
                        spLenTbl[s][d] = minSrcDstDistViaK;
                    }
                }
            }
        }

        // Tracks count of minimum number of destinations reachable from a source
        // (within specified threshold distance)
        int minReachableDestCnt = n + 1;
        // Track max id city with min number of reachable destinations with threshold distance
        int cityWithMinReachableDestinations = -1;
        // Iterate over each source city
        for (auto s = 0; s < n; ++s) {    
            // Compute the number of destination cities reachable within threshold distance
            // from source 'd'
            int nReachableDestinations = 0;
            for (auto d = 0; d < n; ++d) {
                if (spLenTbl[s][d] <= distanceThreshold) {
                    ++nReachableDestinations;
                }
            }
            
            // Update the min count of reachable destinations from a source city
            // and the city (with max id) from where min destinations are reachable 
            if (nReachableDestinations <= minReachableDestCnt) {
                cityWithMinReachableDestinations = s;
                minReachableDestCnt = nReachableDestinations;
            }
        }
        
        return cityWithMinReachableDestinations;
    }
};
