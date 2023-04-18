// e = road.size(), plen = targetPath.size()

// Time complexity : O(plen x e) + O(n + e)
// Space complexity : O(plen x n) + O(n + e)

class Solution {
public:
    vector<int>
    mostSimilar(int n, vector<vector<int>>& roads, vector<string>& names, vector<string>& targetPath) {   
        return mostSimilarViaDP(n, roads, names, targetPath);
    }
    
private:
    
    vector<int>
    mostSimilarViaDP(int nCities, vector<vector<int>>& roads,
                     vector<string>& names, vector<string>& targetPath) { 
        
        // Initialize the road network graph connecting cities
        initGraph(nCities, roads);
        
        int tgtPathLen = targetPath.size();
        // minEditDistTbl[i][j] is the minimum edit distance amongst all possible paths
        // of length 'i' (i.e. consisting of 'i' nodes) which terminate at nodes 'j'; as
        // compared (node by node) with subpath [0, i - 1] of the targetPath
        vector<vector<long> >
            minEditDistTbl(tgtPathLen + 1, vector<long>(nCities, numeric_limits<int>::max()));
        
        // For path length 1, edit distance would be 1 for nodes having same 'name' as the
        // 1st node on the target path, 0 for others
        for (int nodeId = 0; nodeId != nCities; ++nodeId) {
            if (targetPath[0] == names[nodeId]) {
                minEditDistTbl[1][nodeId] = 0;
            } else {
                minEditDistTbl[1][nodeId] = 1;
            }
        }
        
        // prevNodeTbl[i][j] is the id of the previous node on a path of length 'i'
        // (i.e. has 'i' nodes) with the last/'i'th node of the path being node 'j'
        vector<vector<int> > prevNodeTbl(tgtPathLen + 1, vector<int>(nCities, -1));
        
        // Increment the path length sequentially from 2 to target path length
        for (int pLen = 2; pLen <= tgtPathLen; ++pLen) {
            
            // Last node on the partial target path with only the first 'pLen' nodes
            auto & tNodeId = targetPath[pLen - 1];
    
            // Iterate over all possible nodes which can potentially terminate a
            // valid path of length 'pLen' in the road network graph
            for (int nodeId = 0; nodeId != nCities; ++nodeId) {

                // Compute the minimum edit distance of a valid path with 'pLen'
                // nodes which is terminated by current node 'nodeId'; compared to
                // the 1st 'pLen' nodes of target path.
                // Also determine the previous node of this min edit
                // distance path ending at current node
                long minEditDstOfPath = numeric_limits<int>::max();
                
                // The current node 'nodeId' can only be reached from its neighbours.
                // Determine the particular neighbour terminating a valid path
                // of length 'pLen - 1' and with current node 'nodeId' at length
                // 'pLen' having the minimum edit distance
                auto & currNodeNbrsV = _adjListTbl[nodeId];
                for (auto & nbr : currNodeNbrsV) {
                    long editDistOfPath = minEditDistTbl[pLen - 1][nbr];
                    if (tNodeId != names[nodeId]) {
                        // Current node does not have same name as target path node at
                        // 'pLen' => add 1 to edit distance for mismatch
                        editDistOfPath += 1;
                    }
                    
                    if (editDistOfPath < minEditDstOfPath) {
                        // Path of length 'pLen' terminating at 'nodeId' via neighbor 'nbr'
                        // has minimum edit distance compared to target subpath[0, pLen - 1]
                        minEditDstOfPath = editDistOfPath;
                        prevNodeTbl[pLen][nodeId] = nbr;
                    }
                }
                
                // Update the min edit distance for path of length 'pLen'
                // terminating at 'nodeId'
                minEditDistTbl[pLen][nodeId] = minEditDstOfPath;
            }
        }
        
        // Determine the last node of a valid path with same length as target
        // path and having min edit distance compared to target path
        long pathMinEditDistVal = numeric_limits<int>::max();
        int pathLastNode = -1;
        for (int nodeId = 0; nodeId != nCities; ++nodeId) {            
            if (minEditDistTbl[tgtPathLen][nodeId] < pathMinEditDistVal) {
                pathMinEditDistVal = minEditDistTbl[tgtPathLen][nodeId];
                pathLastNode = nodeId;
            }
        }
        
        // From the last node on min edit distance path, backtrack the 
        // previous nodes on the path to get all nodes on the path
        vector<int> minEditDistPathNodesV(tgtPathLen);
        minEditDistPathNodesV[tgtPathLen - 1] = pathLastNode;
        for (int pLen = tgtPathLen; pLen >= 2; --pLen) {
            pathLastNode = prevNodeTbl[pLen][pathLastNode];
            minEditDistPathNodesV[pLen - 2] = pathLastNode;
        }
        
        return minEditDistPathNodesV;
    }

    void
    initGraph(int nCities, vector<vector<int> >& roads) {
        _adjListTbl.resize(nCities);
        // Iterate over each of the roads
        for (auto & road : roads) {
            // Each road forms a bi-directional edge between cities at its endpoints
            auto & u = road[0];
            auto & v = road[1];
            // Add edge to the adjacent list representing road network graph
            _adjListTbl[u].emplace_back(v);
            _adjListTbl[v].emplace_back(u);
        }
    }
    
    // Data members
    // Adjacency list table of the graph which represents
    // the road network connecting the cities
    vector<vector<int> > _adjListTbl;
};
