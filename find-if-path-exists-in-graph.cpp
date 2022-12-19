class Solution {
public:
    bool
    validPath(int n, vector<vector<int>>& edges, int start, int end) {
        
        if (start < 0 || start >= n || end < 0 || end >= n) {
            // Invalid vertices
            return false;
        }
    
        if (start == end) {
            // Identcal source and destination
            return true;
        }
        
        //return validPathViaDFS(n, edges, start, end);
        //return validPathViaBFS(n, edges, start, end);
        return validPathViaUnionFind(n, edges, start, end);
    }
    
private:

    void
    constructGraph(unordered_map<int, vector<int> >& adjacencyList, 
                   vector<vector<int>>& edges) {
        for (auto & e : edges) {
            auto & s = e[0];
            auto & d = e[1];
            adjacencyList[s].emplace_back(d);
            adjacencyList[d].emplace_back(s);
        }
    }
    
    bool
    validPathViaDFS(int n, vector<vector<int>>& edges, int start, int end) {
        
        // Construct graph adjacency list representation
        unordered_map<int, vector<int> > adjacencyList;
        constructGraph(adjacencyList, edges);
        
        vector<bool> visitedV(n, false);
        
        // Commence DFS by adding the start vertex to DFS stack
        stack<int> dfsStk;
        dfsStk.push(start);
        visitedV[start] = true;
        while (!dfsStk.empty()) {
            
            // Pop off and visit the vertex at top of DFS stack
            auto v = dfsStk.top();
            dfsStk.pop();
            
            // Set up all the unvisited neighbours of vertex being visited
            // currently for a DFS visit
            auto & neighboursV = adjacencyList[v];
            for (auto & nv : neighboursV) {
                
                if (end == nv) {
                    // Reached end vertex from start vertex via DFS, so a path
                    // exists between the two
                    return true;
                }
                
                if (!visitedV[nv]) {
                    // Add the unvisited neighbour to top of DFS stack 
                    dfsStk.push(nv);
                    visitedV[nv] = true;
                }
            }
        }
        
        // DFS from start vertex does not hit the end vertex
        return false;
    }
    
    bool
    validPathViaBFS(int n, vector<vector<int>>& edges, int start, int end) {
        
        // Construct graph adjacency list representation
        unordered_map<int, vector<int> > adjacencyList;
        constructGraph(adjacencyList, edges);
        
        vector<bool> visitedV(n, false);
        
        // Commence BFS by enqueueing the start vertex to BFS queue
        queue<int> bfsQ;
        typedef queue<int>::size_type qSzT;
        bfsQ.push(start);
        visitedV[start] = true;
        while (!bfsQ.empty()) {
            
            // Visit all the vertices at the current level
            qSzT qSz = bfsQ.size();
            for (qSzT i = 0; i != qSz; ++i) {
            
                // Dequeue and visit the vertex at front of BFS Q
                auto v = bfsQ.front();
                bfsQ.pop();
            
                // Set up all the unvisited neighbours of vertex being visited
                // currently for a BFS visit in the nxt iteration 
                auto & neighboursV = adjacencyList[v];
                for (auto & nv : neighboursV) {
                
                    if (end == nv) {
                        // Reached end vertex from start vertex via BFS, so a path
                        // exists between the two
                        return true;
                    }
                
                    if (!visitedV[nv]) {
                        // Enqueue the unvisited neighbour to bfsQ
                        bfsQ.push(nv);
                        visitedV[nv] = true;
                    }
                }
            }
        }
        
        // BFS from start vertex does not hit the end vertex
        return false;
    }
    
    void
    makeSet(int n, vector<int>& rootV, vector<int>& rankV) {
        // Create a single element set for each element with the element being the root 
        rootV.resize(n);
        rankV.resize(n);
        for (int i = 0; i != n; ++i) {
            rootV[i] = i;
            rankV[i] = 1;
        }
    }
    
    int
    find(int i, vector<int>& rootV) {
        // Find the set root for element 'i'
        int root = i;
        while (root != rootV[root]) {
            root = rootV[root];
        }
        
        // Traverse all the elements on the path from element 'i' to
        // the set root making all elements on the path point to the
        // root - path compression
        while (i != rootV[i]) {
            int parentOfI = rootV[i];
            rootV[i] = root;
            i = parentOfI;
        }
        
        return root;
    }
    
    void
    merge(vector<int>& rootV, vector<int>& rankV, int i, int j) {
        int iroot = find(i, rootV);
        int jroot = find(j, rootV);
        
        if (iroot == jroot) {
            // i and j belong to same set
            return;
        }
        
        // Merge the smaller set to bigger set
        if (rankV[iroot] < rankV[jroot]) {
            rootV[iroot] = jroot;
            rankV[jroot] += rankV[iroot];
        } else {
            rootV[jroot] = iroot;
            rankV[iroot] += rankV[jroot];
        }
    }
    
    bool
    validPathViaUnionFind(int n, vector<vector<int>>& edges, int start, int end) {
        
        // Create as many sets as the number of vertices with each vertex in its own set
        vector<int> setV;
        vector<int> setSizeV;
        makeSet(n, setV, setSizeV);
        
        // The vertices at the end of each edge are connected by the edge.
        // This will be equivalent to a merge operation on these vertices
        // collapsing them to a single connected component
        // Iterate over all the edges and form the graph connected components
        for (auto & e : edges) {
            merge(setV, setSizeV, e[0], e[1]);
        }
        
        // The start and end vertex should end up in the same connected
        // component post merging if there is a path between them
        return find(start, setV) == find(end, setV);
    }
};
