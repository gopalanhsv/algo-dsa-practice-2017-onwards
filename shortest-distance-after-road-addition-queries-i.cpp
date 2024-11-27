// q => queries.size()
// Time Complexity : O(n + qn)
// Space Complexity : O(n + q)

class Solution {
public:
    vector<int>
    shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        return shortestDistanceViaBfs(n, queries);
    }
    
private:
    
    vector<int>
    shortestDistanceViaBfs(int n, vector<vector<int>>& queries) {
        
        // Init graph and min distance vector
        vector<vector<int> > inEdgesTbl(n);
        vector<int> minDistV(n);
        minDistV[n - 1] = 0;
        for (auto v = n - 2; v >= 0; --v) {
            minDistV[v] = minDistV[v + 1] + 1;
            inEdgesTbl[v + 1].push_back(v);
        }

        queue<int> bfsQ;
        vector<int> queryResultV;
        
        // Process each query in sequence
        for (auto & query : queries) {
            // Vertices of new edge added by query
            auto u = query[0];
            auto v = query[1];
            // Add the edge to graph
            inEdgesTbl[v].push_back(u);
            
            bfsQ.push(v);
            while (!bfsQ.empty()) {
                auto currLvlSz = bfsQ.size();
                for (auto i = 0; i < currLvlSz; ++i) {
                    // Dequeue the vertex at front of BFS Q and visit it
                    auto v = bfsQ.front();
                    bfsQ.pop();

                    auto & nbrV = inEdgesTbl[v];
                    for (auto & u : nbrV) {
                        if (minDistV[v] + 1 < minDistV[u]) {
                            minDistV[u] = minDistV[v] + 1;
                            bfsQ.push(u);
                        }
                    }
                }
            }
            
            queryResultV.push_back(minDistV[0]);
        }
        
        return queryResultV;
    }
};
