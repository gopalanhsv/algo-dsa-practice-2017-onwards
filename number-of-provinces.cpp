class Solution {
public:
    int
    findCircleNum(vector<vector<int>>& isConnected) {
    
        // This problem is akin to finding the number of
        // connected components in a graph, where the graph is
        // has cities as its vertices, connection between the
        // cities being the graph edges. All cities which have direct
        // or indirect connections between them form a single
        // connected component or a province. So number of provinces is
        // the number of connected components in the graph.
        
        // This is easily found by union find wherein each city/vertex
        // is in its own single element connected component initially. The
        // connections between the cities are built via union/merge
        // operation; wherein we merge the different sets in
        // which cities lie if there is a connection between them

        int nCities = isConnected.size();
        
        // Each city lies in its own province/component initially
        vector<int> setV;
        vector<int> setSzV;
        makeSet(nCities, setV, setSzV);
        
        // Iterate through the connections between the cities, and
        // connect the components/provinces of connected citites
        int numProvinces = nCities;
        for (int r = 0; r != nCities; ++r) {
            for (int c = 0; c != nCities; ++c) {
                if (isConnected[r][c]) {
                    // Connection between cities 'r' & 'c'. Merge them
                    // into a single province if they are in different provinces
                    if (merge(r, c, setV, setSzV)) {
                        --numProvinces;
                    }
                }
            }
        }
        
        return numProvinces;
    }
    
private:
    
    void
    makeSet(int n, vector<int>& setV, vector<int>& setSizeV) {
        // Create n single element with each element being the root
        setV.resize(n);
        setSizeV.resize(n);
        for (int i = 0; i != n; ++i) {
            setV[i] = i;
            setSizeV[i] = 1;
        }
    }
    
    int
    find(int i, vector<int>& setV) {
        // Find the root/set id of given element 'i'
        int root = i;
        while (root != setV[root]) {
            root = setV[root];
        }
        
        // Make all elements in the set to which 'i' belongs
        // point to the root/set id - path compression
        while (i != root) {
            int parentOfI = setV[i];
            setV[i] = root;
            i = parentOfI;
        }
        
        return root;
    }
    
    bool
    merge(int i, int j, vector<int>& setV, vector<int>& setSizeV) {
        // Find the root/set ids of sets to which elements
        // 'i' & 'j' belong
        int iroot = find(i, setV);
        int jroot = find(j, setV);
        
        if (iroot == jroot) {
            // No merging as both elements in same set, so no 
            // reduction in the number of components
            return false;
        }
        
        // Merge the smaller set to bigger set
        if (setSizeV[iroot] < setSizeV[jroot]) {
            setV[iroot] = jroot;
            setSizeV[jroot] += setSizeV[iroot];
        } else {
            setV[jroot] = iroot;
            setSizeV[iroot] += setSizeV[jroot];
        }
        
        return true;
    }
};
