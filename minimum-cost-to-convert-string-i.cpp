// e => original.size()/changed.size()
// n => source.size()/target.size()
// Time complexity : O(v + n + (26 ^ 3))
// Space complexity : O((26 ^ 2))

class Solution {
public:
    long long
    minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        
        // Problem is modelled as a graph wherein each alphabetic letter of the string
        // is represented by a graph vertex; transitions/changes from a letter in 'original'
        // to a letter in 'changed' form the graph edges with each edge having a weight
        // as per the 'cost' array. Problem reduces to finding the shortest path length
        // between all letters pairs - i.e. all vertices; and using the shortest path length
        // table to compute the total transition cost from 'source' to 'target'
        
        // Shortest paths between all pairs of vertices is obtained via Floyd Warshall
        // as all edges are non -ve
        const int nVertices = 26;
        vector<vector<long> > spLenTbl(nVertices, vector<long>(nVertices, numeric_limits<int>::max()));
        // Iterate over the char transition table and set up the graph edges
        for (auto i = 0; i != original.size(); ++i) {
            auto u = int(original[i] - 'a');
            auto v = int(changed[i] - 'a');
            spLenTbl[u][v] = min(spLenTbl[u][v], (long)cost[i]);
        }
        // Path len between identical letter pairs is 0
        for (auto v = 0; v < nVertices; ++v) {
            spLenTbl[v][v] = 0;
        }

        // Floyd Warshall
        // Iterate over each possible intermediate letter/state 
        for (auto k = 0; k < nVertices; ++k) {
            // Iterate over all possible original/changed letter pairs
            for (auto o = 0; o < nVertices; ++o) { // Original
                for (auto c = 0; c < nVertices; ++c) { // Changed
                    // Compute the min distance from o->c via letter 'k'
                    long minDistViaK = spLenTbl[o][k] + spLenTbl[k][c];
                    // Update the SP len from o->c to be via letter 'k' if
                    // path from o->c via letter 'k' is shorter
                    spLenTbl[o][c] = min(spLenTbl[o][c], minDistViaK);
                }
            }
        }
        
        // Compute min conversion cost
        long minCost = 0;
        // Iterate over each letter of source/target pair
        for (auto i = 0; i != source.size(); ++i) {
            auto s = int(source[i] - 'a');
            auto t = int(target[i] - 'a');
            // Min conversion cost for current letter in 'source'
            auto & cost = spLenTbl[s][t];
            if (cost >= numeric_limits<int>::max()) {
                // Conversion not possible
                return -1;
            }
            minCost += cost;
        }

        return minCost;
    }
};
