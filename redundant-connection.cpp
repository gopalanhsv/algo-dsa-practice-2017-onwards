// V => num vertices / num edges + 1
// Time complexity : O(V)
// Space complexity : O(V)

class UnionFind {
public:
    
    UnionFind(int n) {
        // Create 'n' sets/connected components and initialize them
        makeSet(n);
    }
    
    bool
    merge(int i, int j) {
        auto iRoot = find(i);
        auto jRoot = find(j);
        if (iRoot == jRoot) {
            // 'i' & 'j' are already in the same set/connected component
            // No union/merge required
            return false;
        }
        
        // 'i' & 'j' are in different set/connected component
        // Merge the smaller set/component to the larger one
        if (_rankV[iRoot] < _rankV[jRoot]) {
            // Merge 'i' set/component to that of 'j'
            _rootV[iRoot] = jRoot;
            _rankV[jRoot] += _rankV[iRoot];
        } else {
            // Merge 'j' set/component to that of 'i'
            _rootV[jRoot] = iRoot;
            _rankV[iRoot] += _rankV[jRoot];
        }
        
        return true;
    }
    
private:
    
    void
    makeSet(int n) {
        // Create 'n' sets/connected components each of size/rank 1
        // with root/ids as self
        _rootV.resize(n);
        _rankV.resize(n, 1);
        for (auto i = 0; i < n; ++i) {
            _rootV[i] = i;
        }
    }
    
    int
    find(int i) {

        auto iRoot = i;
        // Determine the root/set identifier of 'i's connected component
        while (iRoot != _rootV[iRoot]) {
            iRoot = _rootV[iRoot];
        }
        
        // Path compression => Make every ancestor of 'i' on the path from
        // 'i' to the root element point to 'iRoot'
        while (i != _rootV[i]) {
            auto iParent = _rootV[i];
            _rootV[i] = iRoot;
            i = iParent;
        }

        return iRoot;
    }
    
    // Data members
    // Array of set identifiers/root nodes
    vector<int> _rootV;
    // Array of set sizes/ranks
    vector<int> _rankV;
};

class Solution {
public:
    vector<int>
    findRedundantConnection(vector<vector<int>>& edges) {
        // The graph of 'n' vertices [1, n] was a tree prior to the addition of a
        // sole extra edge between any 2 vertices. Since we need to remove the
        // last possible edge from the given list of edges which will revert the
        // graph back to a tree -- the problem reduces to a connected components/
        // union-find problem; i.e find the last possible edge whose removal will
        // not split the connected component comprising of all graph nodes
        
        // As there is only a single edge which is converting tree of 'n' vertices
        // to a graph, while building the tree/graph starting from 'n' connected components
        // using the edges in sequence in order to end up with a tree with '1' connected component;
        // all we need to do is to find the single edge whose addition doesn't result in
        // change in the number of connected components -- i.e. it connects vertices
        // existing in the same component
    
        // Determine the number of graph vertices
        auto nv = 0;
        for (auto & edge : edges) {
            nv = max(nv, max(edge[0], edge[1]));
        }
        
        // Create 'n' connected components - one per vertex
        UnionFind cc(nv);
        
        // Iterate over the edges sequentially
        auto nEdges = edges.size();
        for (auto & edge : edges) {
            // Edge vertices (adjust for 0-indexing)
            auto u = edge[0] - 1;
            auto v = edge[1] - 1;
            
            // Attempt to join/merge edge vertices into the same connected component/graph/tree
            if (!cc.merge(u, v)) {
                // Current edge (u, v) does not result in any change in the number of connected components
                // i.e. its addition does not impact the tree connectivity and it can be removed
                return edge;
            }
        }
        
        // Error condition : Each edge removal impacts the tree connectivity
        return {};
    }
};
