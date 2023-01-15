class ConnComp {
public:
    ConnComp(int n) : _nSets(n) {
        init();
    }
    
    int
    find(int i) {
        // Determine root element for set 'i'
        int iRoot = i;
        while (iRoot != _rootV[iRoot]) {
            iRoot = _rootV[iRoot];
        }
        
        // Path compression. All elements on the path from
        // 'i' to root are made to point to root element
        while (i != _rootV[i]) {
            int iParent = _rootV[i];
            _rootV[i] = iRoot;
            i = iParent;
        }
        
        return iRoot;
    }
    
    void
    merge(int i, int j) {
        // Find root of sets 'i' & 'j'
        int iRoot = find(i);
        int jRoot = find(j);
        
        if (iRoot == jRoot) {
            // 'i' & 'j' in same set. No merge reqd
            return;
        }
        
        // Merge smaller set to larger set
        if (_rankV[iRoot] < _rankV[jRoot]) {
            // Merge set 'i' to set 'j'
            _rootV[iRoot] = _rootV[jRoot];
            _rankV[jRoot] += _rankV[iRoot];
        } else {
            // Merge set 'j' to set 'i'
            _rootV[jRoot] = _rootV[iRoot];
            _rankV[iRoot] += _rankV[jRoot];
        }
    }
    
private:
    
    void
    init() {
        // Create required number of single element sets with each of
        // them pointing to self/having self as set identifiers 
        _rootV.resize(_nSets);
        _rankV.resize(_nSets, 1);
        for (int v = 0; v != _nSets; ++v) {
            _rootV[v] = v;
        }
    }
    
    // Data members
    // Number of sets
    int _nSets;
    // Set root/identifier
    vector<int> _rootV;
    // Set size
    vector<int> _rankV;
};

class Solution {
public:
    int
    numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        
        initGraph(vals, edges);
        
        // Number of vertices
        int nVertices = vals.size();
        
        // Union find/connected components of the graph 
        ConnComp connComp(nVertices);
        
        
        int nTotalGoodPaths = 0;
        // Iterate over the vertices in the ascending order of their values
        for (auto & [val, sameValVtxV] : _valToVertexTbl) {
            
            // 'sameValVtxV' is the set of vertices with identical value 'val'
            
            for (auto & v : sameValVtxV) {
                // Adjacent vertices with same/lesser value as vertex 'v'
                auto & adjVtxV = _adjListTbl[v];
                for (auto & u : adjVtxV) {
                    connComp.merge(v, u);
                }
            }
            
            unordered_map<int, int> sameVtxValGroupSizeTbl;
            for (auto & v : sameValVtxV) {
                auto connCompId = connComp.find(v);
                sameVtxValGroupSizeTbl[connCompId]++;
            }
            
            nTotalGoodPaths += sameValVtxV.size();
            for (auto &[_, groupSize] : sameVtxValGroupSizeTbl) {
                auto nGoodPaths = ((groupSize - 1) * groupSize / 2);
                nTotalGoodPaths += nGoodPaths; 
            }
            
        }
        
        return nTotalGoodPaths;
    }
    
private:
    
    void
    initGraph(vector<int>& vals, vector<vector<int>>& edges) {
        
        // Number of vertices
        int nVertices = vals.size();
        for (int v = 0; v != nVertices; ++v) {
            _valToVertexTbl[vals[v]].emplace_back(v);
        }
        
        // Iterate over each of the edges and build the graph adjacency
        // list table
        for (auto & edge : edges) {
            auto u = edge[0];
            auto v = edge[1];
            if (vals[u] <= vals[v]) {
                _adjListTbl[v].emplace_back(u);
            } else {
                _adjListTbl[u].emplace_back(v);
            }
        }
    }
    
    // Table mapping values to vertices with the respective values
    map<int, vector<int> > _valToVertexTbl;
    
    // Table mapping vertices to adjacent vertices having lower/same values
    // as the key vertex (this table represents the edges which can be used
    // in building good paths)
    unordered_map<int, vector<int> > _adjListTbl;
};
