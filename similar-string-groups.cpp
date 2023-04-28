// n = strs.size(), slen = length of each string
// Time complexity : O(n x n x slen)
// Space complexity : O(n)

class UnionFind {
public:
    UnionFind(int n) {
        makeSet(n);
    }
    
    int
    find(int i) {
        // Determine root element/set identifier of set to which 'i' belongs
        // by moving along the parent elements up the tree representing the set
        int iRoot = i;
        while (iRoot != _rootV[iRoot]) {
            iRoot = _rootV[iRoot];
        }
        
        // Path compression => Make all elements on the path from 'i' to
        // root element point towards the root element
        while (i != _rootV[i]) {
            int iParent = _rootV[i];
            _rootV[i] = iRoot;
            i = iParent;
        }
        
        return iRoot;
    }
    
    bool
    merge(int i, int j) {
        // Determine root elements for set 'i' & 'j'
        int iRoot = find(i);
        int jRoot = find(j);
        
        if (iRoot == jRoot) {
            // Both 'i' & 'j' are in the same set
            // No merge operation required and hence the
            // number of connected components stays same
            return false;
        }
        
        // Merge the smaller sized set to the larger sized set
        if (_rankV[iRoot] < _rankV[jRoot]) {
            // Merge set 'i' to set 'j'
            _rankV[jRoot] += _rankV[iRoot];
            _rootV[iRoot] = _rootV[jRoot];
        } else {
            // Merge set 'j' to set 'i'
            _rankV[iRoot] += _rankV[jRoot];
            _rootV[jRoot] = _rootV[iRoot];
        }

        /// Merge operation and hence the number of connected components reduces by 1
        return true;
    }
    
private:
    
    void
    makeSet(int nSets) {
        // Create 'nSets' each with a single element, the sole element
        // being the root element/set identifier
        _rootV.resize(nSets);
        _rankV.resize(nSets, 1);
        for (int v = 0; v != nSets; ++v) {
            _rootV[v] = v;
        }
    }
    
    // Data members
    // Root element/set identifier for each set
    vector<int> _rootV;
    // Set rank/size for each set
    vector<int> _rankV;
};

class Solution {
public:
    int
    numSimilarGroups(vector<string>& strs) {
        // Problem can be modelled as a graph wherein the various strings in the
        // input array of string are the different vertices of the graph; with
        // edges connecting the vertices/strings having similarity relatioship
        // All strings in a similiar group would then form a connected component
        // of the graph; and the number of similar groups would be the number of
        // connected components of the graph (which is easily computed via
        // union-find/disjoint set)
        
        // Initialize connected components s.t each string forms a connected
        // component solely by itself
        int nVertices = strs.size();
        UnionFind uf(nVertices);
        int nConnectedComponents = nVertices;
        
        // Form all possible pairs of strings (graph vertices) located at
        // disjoint indices
        for (int u = 0; u != nVertices; ++u) {
            for (int v = u + 1; v != nVertices; ++v) {
                auto & s1 = strs[u];
                auto & s2 = strs[v];
                // Check for similarity of strings s1 & s2
                if (areSimilar(s1, s2)) {
                    // Since s1 and s2 are similar, merge the two graph vertices
                    // corresponding to the two strings into the same connected
                    // component
                    if (uf.merge(u, v)) {
                        // s1 and s2 were in two different components prior to
                        // the merge/union operation; now they are in the same
                        // component/group post the merge ops => reduction in the
                        // number of groups/connected components
                        --nConnectedComponents;
                    }
                }
            }
        }

        return nConnectedComponents;
    }
    
private:
    
    bool
    areSimilar(const string& s1, const string& s2) {
        // Strings 's1' & 's2' are similar if they are identical or
        // have identical chars in all locations except 2
        int strSz = s1.size();
        int nDiffCharsAtSameIdx = 0;
        for (int i = 0; i != strSz; ++i) {
            if (s1[i] != s2[i]) {
                ++nDiffCharsAtSameIdx;
            }
        }
        
        return nDiffCharsAtSameIdx == 2 || nDiffCharsAtSameIdx == 0;
    }
};
