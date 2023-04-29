// Q = num queries, E = number of edges, n = num vertices
// Time complexity :  O(n) + O(QlogQ) + O(ElogE)
// Space complexity : O(n) + O(Q) + O(logE) + O(logQ) -> O(n) + O(Q)

class UnionFind {
public:
    UnionFind(int n) {
        makeSet(n);
    }
    
    int
    find(int i) {
        // Determine root element/set identifier of set to which 'i' belongs
        // by moving along the parent elements up the tree representing the set
        int iRoot = i;
        while (iRoot != _rootV[iRoot]) {
            iRoot = _rootV[iRoot];
        }
        
        // Path compression => Make all elements on the path from 'i' to
        // root element point towards the root element
        while (i != _rootV[i]) {
            int iParent = _rootV[i];
            _rootV[i] = iRoot;
            i = iParent;
        }
        
        return iRoot;
    }
    
    bool
    merge(int i, int j) {
        // Determine root elements for set 'i' & 'j'
        int iRoot = find(i);
        int jRoot = find(j);
        
        if (iRoot == jRoot) {
            // Both 'i' & 'j' are in the same set
            // No merge operation required and hence the
            // number of connected components stays same
            return false;
        }
        
        // Merge the smaller sized set to the larger sized set
        if (_rankV[iRoot] < _rankV[jRoot]) {
            // Merge set 'i' to set 'j'
            _rankV[jRoot] += _rankV[iRoot];
            _rootV[iRoot] = _rootV[jRoot];
        } else {
            // Merge set 'j' to set 'i'
            _rankV[iRoot] += _rankV[jRoot];
            _rootV[jRoot] = _rootV[iRoot];
        }

        /// Merge operation and hence the number of connected components reduces by 1
        return true;
    }
    
    int
    maxSetSize() {
        int maxSetSz = 0;
        for (auto setSz : _rankV) {
            maxSetSz = max(maxSetSz, setSz);
        }
        return maxSetSz;
    }
    
private:
    
    void
    makeSet(int nSets) {
        // Create 'nSets' each with a single element, the sole element
        // being the root element/set identifier
        _rootV.resize(nSets);
        _rankV.resize(nSets, 1);
        for (int v = 0; v != nSets; ++v) {
            _rootV[v] = v;
        }
    }
    
    // Data members
    // Root element/set identifier for each set
    vector<int> _rootV;
    // Set rank/size for each set
    vector<int> _rankV;
};

class Solution {
public:
    vector<bool>
    distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        // What is required is a structure/algorithm for collecting all the edges having a weight
        // strictly lesser than a particular limit (enforced by a query); and the respective
        // structure/algorithm should allow quick determination of connectivity/path between the
        // vertices specified in the query. Union-find/Disjoint set easily accomplishes this.

        // Associate each query with the respective index value. This enables the output
        // answers array to be ordered in accordance with the input query ordering
        int nQueries = queries.size();
        for (int i = 0; i != nQueries; ++i) {
            auto & query = queries[i];
            query.emplace_back(i);
        }
        
        // Sort the edges in the non-decreasing order of weights and queries in non-decreasing
        // order of limits; which allows grouping of all queries and edges which are strictly
        // l.t a particular limit/weight value
        auto & edges = edgeList;
        sort(edges.begin(), edges.end(),
             [&](const auto & e1, const auto & e2) {
                return (e1[2] < e2[2]); 
             });
        sort(queries.begin(), queries.end(),
             [&](const auto & q1, const auto & q2) {
                return (q1[2] < q2[2]); 
             });
        
        // Create 'n' connected components/sets each consisting of a single unique vertex
        UnionFind connComponents(n);
        
        int nEdges = edges.size();
        vector<bool> pathExistsV(nQueries, false);
        int currEdgeIdx = 0;
        // Iterate over each query in the non-decreasing order of query 'limit' values
        for (auto & query : queries) {
            auto & currLimit = query[2];

            // Determine all edges having a weight l.t than current query limit and add
            // all such edges/vertices forming the edges to the union-find data structure.
            // The union-find data structure will end up holding all vertices forming
            // edges l.t the reqd query limit; with such vertices having connectivity
            // being grouped into the same connected component/set
            while (currEdgeIdx < nEdges) {
                auto & edge = edges[currEdgeIdx];
                auto & edgeWt = edge[2];
                if (edgeWt >= currLimit) {
                    // Edges in range [currEdgeIdx, ...] having weight exceeding query
                    // limit, so are not processed for now
                    break;
                }
    
                // Edge vertices
                auto & u = edge[0];
                auto & v = edge[1];
                // Add edge to connected components and group
                connComponents.merge(u, v);
                
                // Advance to the next edge
                ++currEdgeIdx;
            }
            
            // Query vertices
            auto & p = query[0];
            auto & q = query[1];
            // Query index as per input query ordering
            auto & qIdx = query.back();
            if (connComponents.find(p) == connComponents.find(q)) {
                // query vertices lie in the same connected component
                // => path exists between the vertices with each edge
                // having a weight l.t current query limit
                pathExistsV[qIdx] = true;
            }
        }

        return pathExistsV;
    }
};
