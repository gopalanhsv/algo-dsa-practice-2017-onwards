// n => num graph vertices/num courses
// e => num graph edges/num prerequisites
// Time complexity : O(n + e)
// Space complexity : O(n + e)

class Solution {
public:
    bool
    canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // The problem is modeled as a DAG with the courses being the
        // graph vertices and prerequisites being the directed edges
        // Prerequisite [a, b] implies a directed edge from b->a as course
        // 'b' must be taken before course 'a'
        
        // If all courses must be finished, then an ordering should exist
        // s.t. traversal starting from courses with no prerequistes allows
        // all courses to be completed. That is, a topological sort of the
        // problem modeled as a DAG should result in all vertices/courses
        // getting included in the ordering
        // Top sort via Kahns' algorithm
        
        // Build the graph adjacency list and indegree vector
        unordered_map<int, vector<int> > adjList;
        vector<int> inDegreeV(numCourses, 0);
        for (auto & prerequisite : prerequisites) {
            auto & src = prerequisite[1];
            auto & dst = prerequisite[0];
            inDegreeV[dst]++;
            adjList[src].emplace_back(dst);
        }

        // Add all the graph vertices with indegree 0, i.e. courses with
        // no prerequisites to the topological sort queue
        queue<int> tsQ;
        for (int v = 0; v != numCourses; ++v) {
            if (0 == inDegreeV[v]) {
                tsQ.push(v);
            }
        }
        
        // Loop and process vertices from the front of topological sort Q
        int nOrderedCourses = 0;
        while (!tsQ.empty()) {
            // Dequeue vertex at Q front (this has an indegree of 0)
            auto v = tsQ.front();
            tsQ.pop();
            // Increment count of ordered vertices
            ++nOrderedCourses;
            
            // Remove the above dequeued node from the graph
            // That is, remove all edges emanating from this vertex
            for (auto & nv : adjList[v]) {
                // Remove edge v --> nv
                if (0 == --inDegreeV[nv]) {
                    // Edge removal results in neighbour vertex 'nv' having
                    // no incoming edge. Add it to topological sorting Q
                    tsQ.push(nv);
                }
            }
            
        }
        
        // All courses should be topologically ordered in order to be finished
        return nOrderedCourses == numCourses;
    }
};
