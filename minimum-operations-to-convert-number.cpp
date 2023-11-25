// n => nums.size()
// Time complexity : 
// At the worst, each of the nums in the range [0, 1000] get visited along with 'start'
// These would be the vertices 'V'. From each of the vertices, 'n' neighbors are checked
// i.e 'n' edges per vertex
// => TC = O(n * r), r is the range size [0, 1000]
// Space complexity : O(r)

class Solution {
public:
    int
    minimumOperations(vector<int>& nums, int start, int goal) {
        if (start == goal) {
            // No ops reqd
            return 0;
        }
        
        // Problem is modeled as a graph wherein 'start', 'goal' along
        // with all the intermediate numbers encountered during the conversions
        // from 'start' to 'goal' are the graph vertices. Graph edges are formed
        // from each number 'x' to the set of numbers which can be obtained
        // from 'x' (i.e. x + nums[i], x - nums[i], x ^ nums[i] where both
        // 'x' and new number are in the range [0, 1000]) i.e. neighbors
        
        // Problem then reduces to doing a BFS traversal from 'start' to 'goal'
        // to determine the minimum number of hops/conversions
        
        queue<int> bfsQ;
        unordered_set<int> visited;
        int nHops = 0;
        // Commence BFS from 'start'
        bfsQ.push(start);
        visited.insert(start);
        while (!bfsQ.empty()) {
            // Visit all the vertices at the current BFS level
            // (i.e. all numbers reachable with the identical number of ops)
            auto currLvlSz = bfsQ.size();
            for (auto i = 0; i != currLvlSz; ++i) {
                // Dequeue and visit the vertex at Q front
                auto x = bfsQ.front();
                bfsQ.pop();
                
                // Schedule all the valid unvisited neighbor vertices reachable from number
                // 'x' in a single operation for a BFS traversal in next iteration
                // From 'x' reachable next hop neighbor vertices/numbers are 'x + num,
                // x - num, x ^ num' where 'num' are each of 'nums' array entries 
                for (auto & num : nums) {
                    auto nX1 = x + num;
                    auto nX2 = x - num;
                    auto nX3 = x ^ num;
                    for (auto & nX : {nX1, nX2, nX3}) {
                        if (nX == goal) {
                            // 'goal' reachable in next operation/one hop
                            return nHops + 1;
                        }
                        // Ignore numbers visited/scheduled for visit and those beyond range [0, 1000]
                        if ((nX >= 0) && (nX <= 1000) && (visited.find(nX) == visited.end())) {
                            visited.insert(nX);
                            bfsQ.push(nX);
                        }
                    }
                }
            }
            // Increment min operations/num hops from numbers seen at current level
            ++nHops;
        }
        // Not possible to hit 'goal' from 'start'
        return -1;
    }
};
