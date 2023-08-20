// Time complexity : O(n^2) as a total of n^2 edges can be present due to dependencies
// Space complexity : O(n^2) as tsQ & adjacency list will end up holding all edges in worst case
class Solution {
public:
    vector<int>
    sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        // Problem is modeled as a directed graph wherein the items are the graph vertices with the
        // directional graph edges being defined by the 'beforeItems' relationship (a directed edge
        // from each vertex in beforeItems[i] to vertex 'i') for items belonging to the same group.
        
        // As each of the items/vertices belonging to the same group must be sorted s.t. they lie
        // next to each other finally; there should be edges between the items/vertices of the
        // same group. Since forming such edges leads to cycles; the relationship between all the
        // items/vertices in the same group being a single entity is captured by having 2 virtual
        // group vertices per group. One of the virtual group vertex would be an ingress vertex
        // to the group and the other virtual group vertex would be the egress vertex from group.
        // Directional edges are present from the ingress virtual group vertex to each of the group
        // members; and from each of the group members to the egress virtual group vertex
        // Any ingress/egress to the group vertices/items is solely via the respective virtual
        // group ingress/egress virtual vertices; and not directly to the group items/vertices/
        // members
        
        // So directional graph edges defined by 'beforeItems' relationship, where item 'i' and
        // a member 'x' of beforeItems[i] are in different groups; the directed edge is formed
        // from egress virtual group vertex of 'x' (or 'x' if x group is -1) TO
        // the ingress virtual group vertex of 'i' (or 'i' if i group is -1)
        
        // All that is required to sort the items is do exec a topological sort (Kahns' algorithm)
        // [this ensures that dependency between the various items is sorted out] and remove the
        // virtual vertices post topsort
        
        _nItems = n;
        // Create the graph
        initGraph(n, m, group, beforeItems);
        
        // Do a topological ordering of the graph
        vector<int> sortedVerticesV;
        topSort(sortedVerticesV);
        
        // The topological ordering should have all the items else sorting has failed
        return sortedVerticesV.size() == n ? sortedVerticesV : vector<int>();
    }
    
private:
    
    void
    initGraph(int nItems, int nGroups, vector<int>& groupIdsV, vector<vector<int>>& beforeItemsTbl) {     
        // Each of the item 'i' in 'nItems' has a vertex with id 'i'
        // Each of the group 'g' in 'nGroups' has 2 virtual vertices
        // an ingress vertex with id 'nItems + 2g' & an egress vertex with id 'nItems + 2g + 1'
        _nVertices = nItems + 2 * nGroups;
        _graphAdjListTbl.resize(_nVertices);
        _inDegreeTbl.resize(_nVertices, 0);
        
        // Build the default intra group relationships between the virtual
        // ingress vertices, group vertices, virtual egress vertices
        // Iterate over each vertex
        for (int v = 0; v != nItems; ++v) {
            auto groupId = groupIdsV[v];
            if (-1 != groupId) {
                
                // Vertex belongs to a valid group
                auto groupIngressVtx = nItems + (groupId << 1);
                auto groupEgressVtx = groupIngressVtx + 1;
                // Edge (group ingress vertex -> 'v')
                _graphAdjListTbl[groupIngressVtx].insert(v);
                _inDegreeTbl[v]++;
                
                // Edge ('v' -> group egress vertex)
                _graphAdjListTbl[v].insert(groupEgressVtx);
                _inDegreeTbl[groupEgressVtx]++;
            }
        }
        
        // Build the relationships between the vertices based on 'beforeItems'
        // Iterate over each vertex
        for (int dstVtx = 0; dstVtx < nItems; ++dstVtx) {
            // Destination of the edge would be either the vertex 'dstVtx' or
            // the ingress group vertex for 'dstVtx'
            auto edgeDstVtx = dstVtx;
            auto dstGroupId = groupIdsV[dstVtx];
            if (-1 != dstGroupId) {
                edgeDstVtx = nItems + (dstGroupId << 1);
            }
            
            // Iterate over each of the possible source/before vertex of 'dstVtx'
            for (auto srcVtx : beforeItemsTbl[dstVtx]) {
                // Source of the edge would be either the vertex 'srcVtx' or
                // the egress group vertex for 'srcVtx'
                auto edgeSrcVtx = srcVtx;
                auto srcGroupId = groupIdsV[srcVtx];
                
                if (srcGroupId == dstGroupId) {
                
                    // Both the src and dst vertices are in same group
                    // Add edge (srcVtx -> dstVtx) as no group jhoomla involved
                    _graphAdjListTbl[srcVtx].insert(dstVtx);
                    _inDegreeTbl[dstVtx]++;
                    
                } else {

                    // src and dst are in different groups
                    if (-1 != srcGroupId) {
                        edgeSrcVtx = nItems + (srcGroupId << 1) + 1;
                    }

                    // Add edge (edgeSrcVtx -> edgeDstVtx)
                    auto iter = _graphAdjListTbl[edgeSrcVtx].find(edgeDstVtx);
                    if (iter == _graphAdjListTbl[edgeSrcVtx].end()) {
                        _graphAdjListTbl[edgeSrcVtx].insert(edgeDstVtx);
                        _inDegreeTbl[edgeDstVtx]++;
                    }
                }
                
            }
        }
    }
    
    void
    topSort(vector<int> & sortedV) {
        // Topsort Q
        queue<int> tsQ;
        typedef queue<int>::size_type qSzT;
        vector<bool> visitedV(_nVertices, false);
        
        // Commence Kahns' algo for topological sort
        
        // Iterate over the vertice starting from group vertices (as we want to
        // do topsort s.t. all the vertices in a group end up together)
        for (auto v = _nVertices - 1; v >= 0; --v) {
            
            // Set up the current vertex 'v' for topsort only if it has '0' indegree
            // i.e no dependencies and has not been explored earlier
            if ((0 == _inDegreeTbl[v]) && !visitedV[v]) {
                tsQ.push(v);
        
                // TOPSORT Instance
                while (!tsQ.empty()) {
                    // Visit and dequeue each of the vertices at the current level
                    qSzT qSz = tsQ.size();
                    for (auto i = 0; i < qSz; ++i) {
                        // Dequeue the vertex at Q front and visit it
                        auto v = tsQ.front();
                        tsQ.pop();
                        visitedV[v] = true;
                        // Add the vertex to top-sorted output if its is non-virtual vertex
                        if (v < _nItems) {
                            sortedV.emplace_back(v);
                        }
                        // Remove the vertex 'v' from the graph; i.e remove all
                        // the edges between vertex 'v' and its adjacent neighbors
                        auto & nbrs = _graphAdjListTbl[v];
                        for (auto & nv : nbrs) {
                            // Edge (v -> nv) removed
                            if (0 == --_inDegreeTbl[nv]) {
                                // Neighbor vertex 'v' has no incoming edges => no dependencies
                                // on items 'nv' post edge removal => add it to topsort Q
                                tsQ.push(nv);
                            }
                        }
                    }
                } // END TOPSORT Instance 
            }
        }
    }
    
    // Data members
    // Graph representing the items/vertices and group, item relationships 
    vector<unordered_set<int> > _graphAdjListTbl;
    // Indegree table (in edges for each graph vertex)
    vector<int> _inDegreeTbl;
    // Num graph vertices
    int _nVertices;
    // Num Items
    int _nItems;
};
