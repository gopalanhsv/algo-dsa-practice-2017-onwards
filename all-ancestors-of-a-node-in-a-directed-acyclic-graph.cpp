// e => edges.size()
// Time complexity : O(e + n^2logn)
// Space complexity : O(n + e)
class Solution {
public:
    vector<vector<int>>
    getAncestors(int n, vector<vector<int>>& edges) {
        
        // Build graph represented by the edges and indegree table
        buildGraph(n, edges);
        
        // Exec a topological sort commencing from each of the nodes with no incoming edges
        // employing Kahns' algorithm
        queue<int> topSortQ;
        for (auto v = 0; v != n; ++v) {
            if (0 == _inDegreeTbl[v]) {
                topSortQ.push(v);
            }
        }

        // List of ancestor nodes seen so far for each vertex arranged in sorted order
        vector<set<int>> ancestorsTbl(n);
        while (!topSortQ.empty()) {
            auto qSz = topSortQ.size();
            // Visit all the nodes/vertices in the top sort Q
            for (auto i = 0; i != qSz; ++i) {
                // Dequeue the vertex at Q front and visit it
                auto currVtx = topSortQ.front();
                topSortQ.pop();
                // Ancestors of the current vertex being visited
                auto & currVtxAncestors = ancestorsTbl[currVtx];
                // Iterate over all the descendents of the current vertex
                auto & descendantsV = _adjListTbl[currVtx];
                for (auto & d : descendantsV) {
                    // All the ancestors of 'currVtx' and 'currVtx' will
                    // be ancestors of the descendant 'd'
                    if (!currVtxAncestors.empty()) {
                        ancestorsTbl[d].insert(currVtxAncestors.begin(), currVtxAncestors.end());
                    }
                    ancestorsTbl[d].insert(currVtx);
                    // Remove the edge (currVtx->d)
                    if (0 == --_inDegreeTbl[d]) {
                        // Descendant 'd' gets scheduled for a topsort visit iff all
                        // its ancestors have been explored/edges from all ancestors removed
                        topSortQ.push(d);
                    }
                }
            }
        }

        // Ancestors for each node converted to required output format
        vector<vector<int> > ancestorsV(n);
        for (auto v = 0; v != n; ++v) {
            auto & ancestors = ancestorsTbl[v];
            for (auto & ancestor : ancestors) {
                ancestorsV[v].emplace_back(ancestor);
            }
        }
        
        return ancestorsV;
    }
    
private:
    
    void
    buildGraph(int n, vector<vector<int> >& edges) {
        _adjListTbl.resize(n);
        _inDegreeTbl.resize(n, 0);
        for (auto & edge : edges) {
            auto & u = edge[0];
            auto & v = edge[1];
            _adjListTbl[u].emplace_back(v);
            _inDegreeTbl[v]++;
        }
    }
    
    // Data members
    // Adjacency list representation of graph
    // _adjListTbl[u] is the list of vertices directly reachable from 'u'
    vector<vector<int> > _adjListTbl;
    // _inDegreeTbl[v] => indegree of graph vertex 'v'
    vector<int> _inDegreeTbl;
};
