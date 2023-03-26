// Time Complexity
// O(num vertices)
// Space Complexity
// O(num vertices)

class Solution {
public:
    int
    longestCycle(vector<int>& edges) {
        // Since each graph vertex can have at most one outedge, 
        // each vertex can be a part of at most one cycle
        
        return longestCycleViaDFS(edges);
    }
    
private:
    
    int
    longestCycleViaDFS(vector<int>& edges) {
        
        // Since each vertex has at most one outedge, a DFS commencing/passing
        // from from a vertex 'v' will visit all the edges/vertices forming the sole
        // cycle (if any) constituted by the vertex; till the DFS returns
        // back to 'v'. All the edges/vertices during the DFS need to be visited
        // only once (as each vertex has at most a single outedge) and backtracking
        // is not required.
        // Vertices which are not a part of the cycle will be visited at most once
        // during DFS as they have no outedge leading to a path back to them via
        // an inedge
        // Since there is at most a single outedge from a vertex, DFS from any
        // vertex reduces to a linked list traversal equivalent
        
        int nVertices = edges.size();
        int maxCycleLen = 0;
        vector<int> nHopsDuringDFSV(nVertices, -1);
        for (int v = 0; v != nVertices; ++v) {
            if ((nHopsDuringDFSV[v] == -1) && (edges[v] != -1)) {
                // Vertex 'v' has not been visited earlier (via a cycle
                // on the DFS path commencing from a earlier seen vertex)
                
                // Commence a DFS from vertex 'v'
                unordered_set<int> seenVerticesTbl;
    
                int currVertex = v;
                int nHopsFromStartVertex = 0;
                while (nHopsDuringDFSV[currVertex] == -1) {
                    
                    nHopsDuringDFSV[currVertex] = nHopsFromStartVertex++;
                    seenVerticesTbl.insert(currVertex);
                    
                    // Find the next vertex along the sole outedge
                    // from current vertex
                    auto & nextVertex = edges[currVertex];
                    if (-1 == nextVertex) {
                        // DFS Path ends at current vertex
                        break;
                    }
                    
                    if (seenVerticesTbl.find(nextVertex) != seenVerticesTbl.end()) {
                        // The next vertex has been visited earlier in the current
                        // DFS iteration. This implies that a cycle goes through 
                        // current vertex and next vertex
                        // Compute this cycle length
                        int cycleLen = nHopsFromStartVertex - nHopsDuringDFSV[nextVertex];
                        // Update the maximum cycle length
                        maxCycleLen = max(maxCycleLen, cycleLen);
                        // Cycle hit, break out of the loop
                        break;
                    }
                    
                    // Advance to next vertex
                    currVertex = nextVertex;
                }
            }
        }
            
        return (0 == maxCycleLen) ? -1 : maxCycleLen;
    }
};
