// n = nums.size(), m = num moves
// Time complexity : O(max(n, m)) + O(max(n, m) x log(max(n, m)))
// Space complexity : O(max(n, m))
class Solution {
public:
    vector<int>
    relocateMarbles(vector<int>& nums, vector<int>& moveFrom, vector<int>& moveTo) {
        // Add all marble locations/positions to hash table
        unordered_set<int> marblePosTbl(nums.begin(), nums.end());
        
        // Simulate the moves sequentially as per input
        int nMoves = moveFrom.size();
        for (int moveId = 0; moveId != nMoves; ++moveId) {
            auto & from = moveFrom[moveId];
            if (marblePosTbl.find(from) != marblePosTbl.end()) {
                // Exec move only if marbles are present at 'from' location
                // Remove all marbles at 'from'
                marblePosTbl.erase(from);
                // Move the marbles to appropriate 'to' location
                auto & to = moveTo[moveId];
                marblePosTbl.insert(to);
            }
        }
        
        // Build sorted final locations/positions of marbles
        vector<int> finalPosV(marblePosTbl.begin(), marblePosTbl.end());
        sort(finalPosV.begin(), finalPosV.end());
        return finalPosV;
    }
};
