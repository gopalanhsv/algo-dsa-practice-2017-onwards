// Time complexity : O(array size) as each index/vertex is visited once
// Space complexity : O(array size) as each index/vertex may be stored in BFS Q
//                    when all indices have same val; and for hash table wherein
//                    each array index has an entry

class Solution {
public:
    int
    minJumps(vector<int>& arr) {
        
        if (arr.size() <= 1) {
            // Base case of single element/empty array
            return 0;
        }
        
        // Problem can be modeled as a graph wherein the array indices represent the
        // graph vertices; and the set of possible jumps from an array index to another
        // index form directional graph edges with jump source array index as source
        // vertex and jump destination array index as destination vertex for the edge
        // Problem then reduces to finding the minimum number of jumps/edges between
        // vertex 0 and the final vertex; which is easily done via BFS traversal
        
        // Initialized tables for the game
        init(arr);
        
        // Do a BFS traversal from source vertex/index 0 to the last index/vertex in
        // the jump game/graph to determine the min number of jumps/edges between the two
        return minPathLen(0, _nVertices - 1, arr);
    }
    
private:
    
    void
    init(vector<int>& arr) {
        // Number of graph vertices = number of array indices
        _nVertices = arr.size();
        
        // Populate hash table grouping each of the array values
        // to the list of indices having the respective values
        for (int i = 0; i != _nVertices; ++i) {
            auto & val = arr[i];
            _valToIndicesTbl[val].emplace_back(i);
        }
    }
    
    int
    minPathLen(int sv, int dv, vector<int>& arr) {
        
        queue<int> bfsQ;
        typedef queue<int>::size_type qSzT;
        vector<bool> visitedV(_nVertices, false);
        // Add source vertex to BFS Q
        bfsQ.push(sv);
        visitedV[sv] = true;
        // Commence BFS
        int nEdges = 0;
        while (!bfsQ.empty()) {
            // Iterate and visit all vertices at the current level
            qSzT currLvlSz = bfsQ.size();
            for (int i = 0; i != currLvlSz; ++i) {
                // Visit the vertex at front of the BFS Q
                auto v = bfsQ.front();
                bfsQ.pop();

                if (v == dv) {
                    // Reached destination/last array index
                    return nEdges;
                }

                // Schedule all the unvisited neighbors of above visited/dequeued
                // vertex 'v' for a BFS visit in the subsequent iteration as per
                // the input jump constraints
                
                // From each array index/source vertex, one can jump to
                // (i.e. have a edge to) destination vertex/array index
                // as follows
                // 1. Jump to immediate next vertex
                if ((v + 1 < _nVertices) && !visitedV[v + 1]) {
                    // Add unvisited neighbor to BFS Q and mark it as visited
                    bfsQ.push(v + 1);
                    visitedV[v + 1] = true;
                }
                // 2. Jump to immediate prior vertex from 'v'
                if ((v - 1) >= 0 && !visitedV[v - 1]) {
                    // Add unvisited neighbor to BFS Q and mark it as visited
                    bfsQ.push(v - 1);
                    visitedV[v - 1] = true;
                }
                // 3. Jump to indices/vertices having same value as the 
                // current vertex 'v'
                auto iter = _valToIndicesTbl.find(arr[v]);
                if (iter != _valToIndicesTbl.end()) {
                    auto & sameValIdxList = iter->second;
                    for (auto & nv : sameValIdxList) {
                        if (!visitedV[nv]) {
                            // Add unvisited neighbor to BFS Q and mark it as visited
                            bfsQ.push(nv);
                            visitedV[nv] = true;
                        }
                    }
                    // Remove the indices list having same value from the hash table
                    // as all these indices would have been visited in current iteration
                    // (so no need to lopp over the same indices and check for visited
                    // status multiple times)
                    _valToIndicesTbl.erase(iter);
                }
            }
            
            // Advance the number of edges/jumps from source vertex for
            // BFS visits scheduled at next level
            ++nEdges;
        }
        
        // Unable to reach destination from source
        return 0;
    }
    
    // Data members
    // Number of vertices in jump game graph
    int _nVertices;
    
    // Hash table grouping each of the array values to the
    // list of indices having the respective values
    unordered_map<int, list<int> > _valToIndicesTbl;
};
