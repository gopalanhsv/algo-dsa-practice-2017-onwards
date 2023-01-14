const int nLowerCaseLetters = 26;

class UF {
public:
    
    UF() {
        init();
    }
    
    int
    find(int i) {
        
        // Find the root of 'i'
        int iRoot = i;
        while (iRoot != _rootV[iRoot]) {
            iRoot = _rootV[iRoot];
        }
        
        // Path compression. Set every element on path from 'i'
        // to its root as the root
        while (i != _rootV[i]) {
            int iParent = _rootV[i];
            _rootV[i] = iRoot;
            i = iParent;
        }
        
        return iRoot;
    }
    
    void
    merge(int i, int j) {
        int iRoot = find(i);
        int jRoot = find(j);
        
        if (iRoot == jRoot) {
            // Both 'i' & 'j' are in the same set
            return;
        }
        
        // Merge the set having a lexicographically larger root value to one
        // having a lexicographically smaller root value
        if (iRoot < jRoot) {
            // Merge set 'j' to set 'i'
            _rootV[jRoot] = _rootV[iRoot];
        } else {
            // Merge set 'i' to set 'j'
            _rootV[iRoot] = _rootV[jRoot];
        }
    }
    
private:
    
    void
    init() {
        // Initialize each set to as single element set
        // corresponding to each of the 26 english alphabets
        // Each set will have its sole element as root
        _rootV.resize(nLowerCaseLetters);
        for (int i = 0; i != nLowerCaseLetters; ++i) {
            _rootV[i] = i;
        }
    }
    
    // Data members
    
    vector<int> _rootV;
};

class Solution {
public:
    string
    smallestEquivalentString(string s1, string s2, string baseStr) {
        // Chars which are equivalent should be grouped together so that
        // any one of them can be replaced by the other
        // The problem can be modeled as a graph wherein the chars form the graph
        // vertices and an equivalence relation between 2 chars is modeled by an
        // edge between the respective vertices. All the chars which are equivalent
        // and should be grouped together end up in the same connected component
        // of the graph; while chars which are not equivalent lie in distinct
        // connected components. For find the smallest equivalent string, each
        // char in the base string should be replaced by lexicographically the
        // smallest char which shares the same connected component as the original char.
        
        // The above reduces to a disjoint set union-find operation
        // Each char in initially in its own set. Equivalent between 2 chars
        // implies a merge operation. The root of each set is set to
        // lexicographically the smallest char in the set (to make task finding
        // the smallest equivalent string easier). Due to this fact, the operation
        // of maintaining set size/rank is not done in this version of union find
    
        // Connected components of the graph modelling the equivalent chars
        UF connComp;
        
        int strSz = s1.size();
        // Iterate over the chars in the two string and build the connected
        // components modelling equivalent chars
        for (int i = 0; i != strSz; ++i) {
            // Chars at same location in s1 and s2 are equivalent
            // So the sets representing them are equivalent and should
            // be in the same connected component
            auto s1CharSetId = int(s1[i] - 'a');
            auto s2CharSetId = int(s2[i] - 'a');
            connComp.merge(s1CharSetId, s2CharSetId);
        }
        
        // Iterate over the chars in the base string sequentially
        int baseStrSz = baseStr.size();
        string smallestStr;
        for (int i = 0; i != baseStrSz; ++i) {
            // Connected component to which current char belongs
            auto setId = int(baseStr[i] - 'a');
            auto connCompId = connComp.find(setId);
            // Smallest lexicographic char in the particular component
            // is used to rebuild the base string
            auto smallestChr = 'a' + connCompId;
            smallestStr += smallestChr;
        }
        
        return smallestStr;
    }
};
