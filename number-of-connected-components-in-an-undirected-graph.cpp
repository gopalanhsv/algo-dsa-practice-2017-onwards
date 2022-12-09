class Solution {
public:
    int
    countComponents(int n, vector<vector<int>>& edges) {
        // Use union find
        // Let each vertex be in its own single element component
        // (i.e. single element set). Iterate through the edges, merging
        // the sets in which the vertices forming the edge lie via
        // union-find. The number of sets at the end of the processing
        // all edges would be the number of connected components
        vector<int> setV;
        vector<int> setSizeV;
        
        // Make n sets, each having a single vertex
        makeSet(n, setV, setSizeV);
        int numConnComponents = n;
        
        // Iterate through the edges, merging the sets to which
        // vertices forming an edge belong
        for (auto & e : edges) {
            if (setUnion(e[0], e[1], setV, setSizeV)) {
                --numConnComponents;
            }
        }
        
        return numConnComponents;
    }
    
private:
    
    void
    makeSet(int n, vector<int>& setV, vector<int>& setSizeV) {
        setV.resize(n);
        setSizeV.resize(n);
        // Create 'n' set of numbers with parent of each set being the
        // number itself
        for (int i = 0; i != n; ++i) {
            setV[i] = i;
            setSizeV[i] = 1;
        }
    }
    
    int
    find(int i, vector<int>& setV) {
        // Keep going up the set till root is reached
        int root = i;
        while (root != setV[root]) {
            root = setV[root];
        }

        // Path compression. All nodes on path from node i to root
        // are made to point to root node
        while (i != setV[i]) {
            int parentOfI = setV[i];
            setV[i] = root;
            i = parentOfI;
        }
        
        return root;
    }
    
    bool
    setUnion(int i, int j, vector<int>& setV, vector<int>& setSizeV) {
        // Merge the 2 sets to which 'i' and 'j' belong
        int iroot = find(i, setV);
        int jroot = find(j, setV);
        
        if (iroot == jroot) {
            // Both in same set, no union reqd
            return false;
        }
        
        // Merge smaller set to bigger set
        if (setSizeV[iroot] < setSizeV[jroot]) {
            setV[iroot] = jroot;
            setSizeV[jroot] += setSizeV[iroot];
        } else {
            setV[jroot] = iroot;
            setSizeV[iroot] += setSizeV[jroot];
        }
        
        // 2 sets merged, so number of sets which disappears is 1
        return true;
    }
};
