// nE => num equations, nQ => num queries
// DFS Approach
// Time complexity : O(nE x nQ)
// Space complexity : O(nE)

class Solution {
public:
    vector<double>
    calcEquation(vector<vector<string>>& equations,
                 vector<double>& values,
                 vector<vector<string>>& queries) {
        
        // The problem reduces to a directed graph problem wherein:-
        // If an equatilons[] entry is s.t. numerator is A, denominator is B
        // with a value of 'V' in values[]; A & B represent the vertices of
        // a directed graph with an edge from A to B having a value of V;
        // and an edge from B to A with a value of 1/V

        // Each queries[] entry having numerator C, denominator D then reduces
        // to finding the shortest path from C to D in the above graph via
        // DFS/BFS; and taking the product of all edge weights along the
        // shortest path for getting the value of C / D. If no path exists,
        // answer is taken a -1.0 and if C and D are identical, answer is 1.0

        buildGraph(equations, values);

        vector<double> answersV;
        // Iterate over all queries
        for (auto & query : queries) {
            // Source and destination vertices from queries
            auto & src = query[0];
            auto & dst = query[1];
            if (_graph.find(src) == _graph.end() ||
               _graph.find(dst) == _graph.end()) {
                // Source and/or destination vertex absent from graph
                answersV.emplace_back(-1.0);
            } else if (src == dst) {
                // Source and destination vertex are same
                answersV.emplace_back(1.0);
            } else {
                // Source and destination vertex are different
                // DFS fron source to destination to get the path value
                answersV.emplace_back(pathCostViaDfs(src, dst));
            }
        }
        
        return answersV;
    }
    
private:
        
    void
    buildGraph(vector<vector<string>>& equations, vector<double>& values) {
        // Iterate over all equations and corresponding values. Use them to
        // construct the graph
        for (int i = 0; i != equations.size(); ++i) {
            // Vertices fron equations and edge cost from values[]
            auto & u = equations[i][0];
            auto & v = equations[i][1];
            auto & wt = values[i];
            EdgeInfoT e1, e2;
            e1.dst = v;
            e1.cost = wt;
            e2.dst = u;
            e2.cost = 1 / wt;
            // Populate the graph
            _graph[u].emplace_back(e1);
            _graph[v].emplace_back(e2);
        } 
    }
    
    double
    pathCostViaDfs(string & src, string & dst) {
        // Commence DFS from source vertex to destination vertex
        // and compute path cost
        unordered_set<string> visited;
        stack<pair<string, double> > dfsStk;
        dfsStk.push({src, 1.0});
        
        while (!dfsStk.empty()) {
            // Pop off the vertex at top of stack and visit it
            auto & vertexPathCostP = dfsStk.top();
            // Path cost to popped off vertex from source
            auto pathCost = vertexPathCostP.second;
            auto vertex = vertexPathCostP.first;
            dfsStk.pop();
            
            if (vertex == dst) {
                // Popped off vertex is the destination vertex
                // Return the path cost to the destination from source
                return pathCost;
            }
            
            // Setup all the unvisited immediate neighbours reachable from the
            // currently popped off vertex for a DFS visit in the
            // subsequent iterations
            auto & neighboursV = _graph[vertex];
            for (auto & nbr : neighboursV) {
                auto & nbrVertex = nbr.dst;
                if (visited.find(nbrVertex) == visited.end()) {
                    // Also update the path cost for reach neighbour
                    // vertex from source
                    visited.insert(nbrVertex);
                    dfsStk.push({nbrVertex, pathCost * nbr.cost});
                }
            }
        }
        
        // Destination vertex unreachable from source
        return -1.0;
    }
        
    // Data members
    // Undirected graph edge representation
    typedef struct _EdgeInfoT {
        // Edge destination vertex
        string dst;
        // Edge weight/cost
        double cost;
    } EdgeInfoT;
        
    // Adjacency list representation of a graph mapping each possible source
    // vertex to the list of edges (destinations + edge weight) emanating
    // from the vertex
    unordered_map<string, vector<EdgeInfoT> > _graph;
};
