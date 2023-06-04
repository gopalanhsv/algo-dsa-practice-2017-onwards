// n => number of cities (isConnected.size())
// Time complexity : O(n x n)
// Space complexity : O(n)
class Solution {
public:
    int
    findCircleNum(vector<vector<int>>& isConnected) {
    
        // This problem is akin to finding the number of connected components in a graph,
        // where the graph has cities as its vertices, connection between the cities
        // being the graph edges. All cities which have direct or indirect connections
        // between them form a single connected component or a province. So number of
        // provinces is the number of connected components in the graph.
        
        // Use union find to determine connected components, wherein each city/vertex
        // is in its own single element connected component initially. The connections
        // between the cities are built via union/merge operation; wherein we merge the
        // different sets in which cities lie if there is a connection between them
        int nCities = isConnected.size();
        
        // Each city lies in its own province/component initially
        vector<int> rootV; // Set/connected component identifier
        vector<int> rankV; // Rank/connected component size
        makeSet(nCities, rootV, rankV);
        
        // Iterate through the connections between the cities, and
        // connect the components/provinces of connected citites
        int numProvinces = nCities;
        for (int r = 0; r != nCities; ++r) {
            for (int c = 0; c != nCities; ++c) {
                if (isConnected[r][c]) {
                    // Connection between cities 'r' & 'c'. Merge them
                    // into a single province if they are in different provinces
                    if (merge(r, c, rootV, rankV)) {
                        --numProvinces;
                    }
                }
            }
        }
        
        return numProvinces;
    }
    
private:
    
    void
    makeSet(int n, vector<int>& rootV, vector<int>& rankV) {
        // Create 'n' single element sets with each element being the root
        rootV.resize(n);
        rankV.resize(n);
        for (int i = 0; i != n; ++i) {
            rootV[i] = i;
            rankV[i] = 1;
        }
    }
    
    int
    find(int i, vector<int>& rootV) {
        // Find the root/set id of given element 'i'
        int root = i;
        while (root != rootV[root]) {
            root = rootV[root];
        }
        
        // Make all elements in the set to which 'i' belongs
        // point to the root/set id - path compression
        while (i != root) {
            int parentOfI = rootV[i];
            rootV[i] = root;
            i = parentOfI;
        }
        
        return root;
    }
    
    bool
    merge(int i, int j, vector<int>& rootV, vector<int>& rankV) {
        // Find the root/set ids of sets to which elements
        // 'i' & 'j' belong
        int iroot = find(i, rootV);
        int jroot = find(j, rootV);
        
        if (iroot == jroot) {
            // No merging as both elements in same set, so no 
            // reduction in the number of components
            return false;
        }
        
        // Merge the smaller set to bigger set
        if (rankV[iroot] < rankV[jroot]) {
            rootV[iroot] = jroot;
            rankV[jroot] += rankV[iroot];
        } else {
            rootV[jroot] = iroot;
            rankV[iroot] += rankV[jroot];
        }
        
        return true;
    }
};
