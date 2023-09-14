// E => num flights, V => num airports
// Time complexity : O(E) + O(Vlog(E/V)) on the average with itineraries are distributed
// equally amongst airports OR O(E) + O(VlogV) in worst case with clustered itineraries
// Space complexity : O(E) + O(v)
class Solution {
public:
    vector<string>
    findItinerary(vector<vector<string>>& tickets) {
        // The problem is reduced to a graph problem wherein the various airports
        // form the graph vertices and the tickets form the directed edges, with
        // the edge being from ticket 'from' airport/vertex to the 'to' airport/vertex
        
        // The valid itinerary reduces to a walk/traversal of the graph wherein all 
        // edges are traversed once and only once -- which is akin to doing a Eulerian
        // tour of the graph => Usage of the Heizerholer algo.

        // Since it is mentioned that a valid itinerary exists and the tour should 
        // commence from airport "JFK", there wont be any check for existence of a
        // Eulerian path/tour and the traversal will commence from "JFK"
        // Amongst the (multiple) valid itineraries, the itinerary with the smallest
        // lexical order has to be chosen => the Eulerian tour finding algorithm will
        // be slightly modified s.t at vertex, for processing the unprocessed/unexplored
        // edges leading outward, prefer exploring the edge leading to a vertex with
        // smallest lexical name prior to other unexplored edges. This greedy approach
        // of optimizing locally (choosing lexically the smallest next hop from each
        // vertex) leads to global optimization i.e smallest lexical Eulerian path.
        
        // Build airport graph
        initGraph(tickets);
        list<string> eulerianPath;
        // Exec a Euler tour
        string startVertex("JFK");
        eulerianPathViaDFS(startVertex, eulerianPath);
        return {eulerianPath.begin(), eulerianPath.end()};
    }
    
private:
    
    void
    initGraph(vector<vector<string>>& tickets) {
        // Build the graph of airports with edges as itinerary
        for (auto & ticket : tickets) {
            auto & src = ticket[0];
            auto & dst = ticket[1];
            _adjListTbl[src].emplace_back(dst);
        }
        
        // Iterate over each graph vertex
        for (auto & ent : _adjListTbl) {
            // ent => entry
            // Array of destinations/next hops reachable from source 'ent.first'
            auto & destListV = ent.second;
            // Sort the list of nexthops in lexical order so that the next
            // hops are explored with the smallest next hop first. The sorting
            // is done in reverse order here as the vector for each vertex will
            // be explored from back to front dropping off the visited edge from
            // graph prior to traversal (and vector pop_back is O(1) while pop_front
            // is O(n))
            sort(destListV.begin(), destListV.end(), greater<string>());
        }
    }
    
    void
    eulerianPathViaDFS(string& currVertex, list<string>& eulerianPath) {
        // Visit all the outgoing edges/next hops from the current vertex/airport
        // from the smallest lexical order to the largest
        auto & nextHopsV = _adjListTbl[currVertex];
        while (!nextHopsV.empty()) {
            string nextVertex = nextHopsV.back();
            // Remove the edge leading to the next hop
            nextHopsV.pop_back();
            // Recursively traverse the edge/Explore the next hop/vertex
            eulerianPathViaDFS(nextVertex, eulerianPath);
        }
        
        // Add the current vertex to front of eulerian path
        eulerianPath.push_front(currVertex);
    }

    // Data members
    // Adjacency list representation of the itinerary/airport graph
    unordered_map<string, vector<string> > _adjListTbl;
};
