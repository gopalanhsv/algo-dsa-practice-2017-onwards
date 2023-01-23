class Solution {
public:
    int
    findJudge(int n, vector<vector<int>>& trust) {
        return findJudgeSpaceOptimized(n, trust);
        //return findJudgeNonOptimized(n, trust);
    }
    
private:
    
    int
    findJudgeSpaceOptimized(int n, vector<vector<int>>& trust) {
    
        // Problem is modeled as a directed graph with vertices being the people
        // 1 to n; and edges representing the trust relationships
        // [a, b] => a trusts b => an edge from 'a' to 'b'   
        if (trust.size() < n - 1) {
            // Number of trust relationships/edges being less than the minimum
            // edges reqd for full connectivity (implies no town judge as he 
            // connects to all)
            return -1;
        }
        
        // Construct the graph
        // Compute the indegree and out degree for each vertex. Store the
        // difference between indegree and outdegree for each person/vertex
        vector<int> differenceBetweenInAndOutDegreeV(1 + n, 0);
        for (auto & edge : trust) {
            // Add +1 for incoming edge
            differenceBetweenInAndOutDegreeV[edge[1]]++;
            // Add -1 for outgoing edge
            differenceBetweenInAndOutDegreeV[edge[0]]--;
        }
        
        // Iterate over all people/vertices and get the town judge
        for (int v = 1; v <= n; ++v) {
            // Town judge is trusted by all and trusts no one. So would be the
            // vertex with all incoming edges and no outgoing edges i.e. vertex
            // with difference between indegree and outdegree being n - 1
            if (differenceBetweenInAndOutDegreeV[v] == n - 1) {
                return v;
            }
        }
        
        // No town judge found
        return -1;
    }
    
    int
    findJudgeNonOptimized(int n, vector<vector<int>>& trust) {
    
        // Problem is modeled as a directed graph with vertices being the people
        // 1 to n; and edges representing the trust relationships
        // [a, b] => a trusts b => an edge from 'a' to 'b'
        
        if (trust.size() < n - 1) {
            // Number of trust relationships/edges being less than the minimum
            // edges reqd for full connectivity (implies no town judge as he 
            // connects to all)
            return -1;
        }
        
        // Construct the graph out and indegree vectors
        vector<int> inDegreeV(1 + n, 0);
        vector<int> outDegreeV(1 + n, 0);
        for (auto & edge : trust) {
            inDegreeV[edge[1]]++;
            outDegreeV[edge[0]]++;
        }
        
        // Iterate over all people/vertices and get the town judge
        for (int v = 1; v <= n; ++v) {
            // Town judge is trusted by all and trusts no one. So would be the
            // vertex with all incoming edges and no outgoing edges
            if (outDegreeV[v] == 0 && inDegreeV[v] == n - 1) {
                return v;
            }
        }
        
        // No town judge found
        return -1;
    }
};
