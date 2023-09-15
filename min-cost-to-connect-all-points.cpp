// n => points.size(), e => Num graph edges = n ^ 2
// Time complexity : O(eloge) + O(n)
// Space complexity : O(e) + O(n)
class ConnectedComponents {
public:
    
    ConnectedComponents(){}
    
    // Create 'n' connected components each of size 1
    // and having root as self
    void
    createComponents(int n) {
        _rootTbl.resize(n);
        _rankTbl.resize(n);
        for (int id = 0; id != n; ++id) {
            _rootTbl[id] = id;
            _rankTbl[id] = 1;
        }
    }
    
    // Return 'true' if the given 2 components are
    // connected, 'false' otherwise
    bool
    areConnected(int id1, int id2) {
        // Check if the 2 components have the same root
        return find(id1) == find(id2);
    }
    
    // Connect the 2 given components, so that they end
    // up in the same component
    void
    connectComponents(int id1, int id2) {
        merge(id1, id2);
    }
    
private:
    
    int
    find(int i) {
        
        // Find the root of component 'i'
        int iroot = i;
        while (iroot != _rootTbl[iroot]) {
            iroot = _rootTbl[iroot];
        }
        
        // Make all ancestors/components on the path from node 'i' to the
        // root point to the root - path compression
        while (i != _rootTbl[i]) {
            int parentOfI = _rootTbl[i];
            _rootTbl[i] = iroot;
            i = parentOfI;
        }
        
        return iroot;
    }
    
    void
    merge(int i, int j) {
        // Find the roots of the given 2 components 'i' & 'j'
        int iroot = find(i);
        int jroot = find(j);

        if (iroot == jroot) {
            // Return if the 2 components are connected
            return;
        }
        
        // Attach/merge the smaller sized component to the larger component
        if (_rankTbl[iroot] < _rankTbl[jroot]) {
            _rootTbl[iroot] = jroot;
            _rankTbl[jroot] += _rankTbl[iroot];  
        } else {
            _rootTbl[jroot] = iroot;
            _rankTbl[iroot] += _rankTbl[jroot];
        }
    }
    
    // Data members
    // Array of connected component identifiers
    vector<int> _rootTbl;
    // Array of connected component sizes
    vector<int> _rankTbl;
};

class Solution {
public:
    
    int
    minCostConnectPoints(vector<vector<int> >& points) {
        // The points are modeled as graph vertices and virtual connection
        // between points are the graph edges. Problem reduces to finding
        // cost of the MST which connects/spans all the points
        return mstCostUsingKruskal(points);
    }
    
    // Models Edge connecting the points at indices p1 & p2
    typedef struct _EdgeT {
        int p1;
        int p2;
        int len; // Manhattan distance between point 'p1' & 'p2'
    } EdgeT;
    
private:
    
    int
    mstCostUsingKruskal(vector<vector<int> >& points) {
        // Build the graph formed by the points
        buildGraph(points);
    
        // Kruskal commences here
        // Sort the edges in ascending order of edge lengths
        struct EdgeCmpObj {
            bool
            operator() (const EdgeT& e1, const EdgeT& e2) {
                return e1.len < e2.len;
            }
        };
        sort(_edgesV.begin(), _edgesV.end(), EdgeCmpObj());
        
        // Process the edges in the ascending order of their lengths
        // and build the MST
        int mstCost = 0;
        for (auto & e : _edgesV) {
            // Edge vertices
            auto & u = e.p1;
            auto & v = e.p2;
            // Check if the edge vertices lie in the same connected component
            if (!_connComponents.areConnected(u, v)) {
                // Edge vertices do not lie in same connected component. So this
                // edge forms the MST. Add the edge to MST and connect the
                // edge vertices components
                _connComponents.connectComponents(u, v);
                mstCost += e.len;
            }
        }
        
        return mstCost;
    }
    
    void
    buildGraph(vector<vector<int> >& points) {
        // Form a fully connected graph between the points
        // Also form a connected component for each point
        int nPoints = points.size();
        _connComponents.createComponents(nPoints);
        
        // Connect all disjoint pairs of points by forming an
        // edge between them and add edge to graph
        for (int i = 0; i != nPoints; ++i) {
            auto & p1 = points[i];
            for (int j = i + 1; j != nPoints; ++j) {
                auto & p2 = points[j];
                EdgeT e;
                e.p1 = i;
                e.p2 = j;
                // Edge length is the taxi distance
                e.len = abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
                _edgesV.emplace_back(e);
            }
        }
    }
    
    // Data members
    // Array of all possible edges 
    vector<EdgeT> _edgesV;
    // Tracks connected components formed by the points and connections between them
    ConnectedComponents _connComponents;
};
