// Time complexity :  O(num vertices + num edges)
// Space complexity : O(num vertices)

class ConnComponent {
public:
    ConnComponent(int nVertices) : _rootV(nVertices), _rankV(nVertices, 1) {
        // Initially each graph vertex forms a
        // connected component by itself of size 1
        for (int v = 0; v != nVertices; ++v) {
            _rootV[v] = v;
        }
    }

    void
    connect(int i, int j) {
        // Connect the components in which vertex 'i' & 'j' belong
        merge(i, j);
    }
    
    vector<int>
    getNumVerticesPerConnComponent() {
        // Tracks the components/root vertices which have been visited
        unordered_set<int> seenComponents;
        // Array with number of vertices per connected component
        vector<int> numVerticesV;
        // Iterate over each vertex sequentially
        int nVertices = _rootV.size();
        for (int v = 0; v != nVertices; ++v) {
            // Determine the root vertex/connected component
            // to which current vertex belongs
            int ccId = find(v);
            if (seenComponents.find(ccId) == seenComponents.end()) {
                // Add connected component size to output vector only once
                numVerticesV.emplace_back(_rankV[ccId]);
                seenComponents.insert(ccId);
            }
        }
        
        return numVerticesV;
    }

private:
    
    int
    find(int i) {
        // Root vertex of the connected component to which 'i' belongs
        int iRoot = i;
        while (iRoot != _rootV[iRoot]) {
            iRoot = _rootV[iRoot];
        }
        
        // Path compression -- All vertices on the path from 'i' to the root
        // vertex have their respective root vertices updated to 'iRoot'
        while (i != _rootV[i]) {
            int iParent = _rootV[i];
            _rootV[i] = iRoot;
            i = iParent;
        }
            
        return iRoot;
    }

    void
    merge(int i, int j) {
        // Determine connected component ids/root vertices of components
        // to which 'i' & 'j' belong
        int iRoot = find(i);
        int jRoot = find(j);
        if (iRoot == jRoot) {
            // 'i' & 'j' are in the same connected component
            return;
        }
        
        // Merge the smaller sized component into the larger sized one
        if (_rankV[iRoot] < _rankV[jRoot]) {
            // Merge component 'iRoot' to 'jRoot'
            _rootV[iRoot] = jRoot;
            _rankV[jRoot] += _rankV[iRoot];
        } else {
            // Merge component 'jRoot' to 'iRoot'
            _rootV[jRoot] = iRoot;
            _rankV[iRoot] += _rankV[jRoot];
        }
    }
    
    // Data members
    // Connected component id/root vertex for each graph vertex
    vector<int> _rootV;
    // Size of connected component/num vertices per connected component
    // per root vertex/connected component id  
    vector<int> _rankV;
};

class Solution {
public:
    long long
    countPairs(int n, vector<vector<int>>& edges) {
        // Reduce the graph to its connected components
        ConnComponent cc(n);
        // Add all edges to graph and update the connected components
        for (auto & e : edges) {
            auto & u = e[0];
            auto & v = e[1];
            cc.connect(u, v);
        }
        
        // Each of the nodes in a particular connected component are
        // unreachable from the nodes outside the component. So each
        // node in a connected component can form an unreachable pair
        // with the nodes in other connected components
        // Connected component sizes/num vertices
        vector<int> ccSizesV = cc.getNumVerticesPerConnComponent();
        int nComponents = ccSizesV.size();
        long long nPairs = 0;
        int nVerticesSeenSoFar = 0;
        // Iterate over each connected component
        for (int i = 0; i < nComponents; ++i) {
            long long iConnCompSz = ccSizesV[i];
            // Update the number of vertices seen in the components
            // explored so far
            nVerticesSeenSoFar += iConnCompSz;
            // All vertices in the current connected component form
            // unreachable pairs with the vertices in other components
            // The vertices seen in the earlier explored components are
            // dropped to avoid double counting
            nPairs += (iConnCompSz * (n - nVerticesSeenSoFar));
        }
        
        return nPairs;
    }
    
private:
};
