// e => edges.size()
// Time complexity : O(e + n)
// Space complexity : O(n)

class Solution {
public:
    int
    findChampion(int n, vector<vector<int>>& edges) {
        // DAG => no cycles
        // Edge u -> v => team u is stronger than team v

        // For there to be a unique champion, all teams except the champion team should
        // be weaker than the champion team
        // => Vertices representing all teams other than the champion should have incoming
        // edges s.t a directed path exists from the champion to each other team via the
        // graph with no cycles; s.t all teams are reachable from the champion team vertex
        // leading to the champion being the strongest. Presence of a vertex unreachable
        // from the champion => that team strength may be at same level as champion
        // which is contradictory
        
        // Champion => no other team dominating it => requirement that champion team
        // vertex has no incoming edges => champion team vertex has indegree of 0
        
        // All non-champion team vertices should have at least one incoming edge (which
        // lies on a path from the champion vertex) => all nonchampion vertices should
        // have non-zero indegree
        
        // Conclusion :- For there to be a unique champion, there should be a unique
        // vertex with 0 degree being the champion; and all non-champions should have 
        // have non-0 indegree

        // Compute indegree for each graph vertex
        vector<int> inDegreeTbl(n, 0);
        for (auto & e : edges) {
            // Edge e[0] -> e[1]
            inDegreeTbl[e[1]]++;
        }
        
        auto nChampions = 0;
        auto champion = -1;
        for (auto v = 0; v < n; ++v) {
            if (0 == inDegreeTbl[v]) {
                // Found a candidate champ
                champion = v;
                if (++nChampions > 1) {
                    // Multiple champions possible => no unique champ
                    return -1;
                }
            }
        }
        
        return champion;
    }
};
