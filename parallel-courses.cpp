// e => relations.size() / num graph edges
// Time complexity : O(e + n)
// Space complexity : O(e + n)
class Solution {
public:
    int
    minimumSemesters(int n, vector<vector<int>>& relations) {
    
        // The problem can be modeled as a DAG wherein the vertices are the courses and
        // the directed edges are the course relationships i.e. [prevCourse, nextCourse]
        // implies an edge from vertex 'prevCourse' to 'nextCourse'
        
        // Minimum semesters in this case would be determined by a topological sort of the
        // graph, i.e commencing with vertices having no prerequisites and successively
        // removing such vertices till all graph vertices get removed. The number of
        // semesters would be the number of topological sort levels
        
        // Construct graph adjacency list and indegree vector
        vector<int> inDegreeV(n + 1, 0);
        unordered_map<int, vector<int> > adjList;
        for (auto & relation : relations) {
            auto & pc = relation[0];
            auto & nc = relation[1];
            inDegreeV[nc]++;
            adjList[pc].emplace_back(nc);
        }
        
        // All vertices with zero indegree (courses with no prerequisites) are
        // added to the topological sort Q
        queue<int> tsQ;
        for (int v = 1; v <= n; ++v) {
            if (0 == inDegreeV[v]) {
                tsQ.push(v);
            }
        }
        
        int minSemesters = 0;
        int nRemovedVertices = 0;
        while (!tsQ.empty()) {
            // Complete all courses with no dependencies in this semester
            // (i.e. all courses in the topo sort queue)
            typedef queue<int>::size_type qSzT;
            qSzT qSz = tsQ.size();
            for (qSzT i = 0; i != qSz; ++i) {
                // Dequeue vertex at the front of Q
                auto v = tsQ.front();
                tsQ.pop();
                
                // Complete the course represented by dequeued vertex by removing it
                // from graph. Also remove all edges commencing from the vertex
                ++nRemovedVertices;
                for (auto & nv : adjList[v]) {
                    // Remove edge v -> nv
                    if (0 == --inDegreeV[nv]) {
                        // v --> nv edge removal results in vertex nv with no
                        // course prerequisite. Add this to toposort Q
                        tsQ.push(nv);
                    }
                }
            }
            
            // Increment the number of semesters elapsed
            ++minSemesters;
        }
        
        if (nRemovedVertices != n) {
            // All courses could not be explored/ completed
            return -1;
        }
        
        return minSemesters;
    }
};
