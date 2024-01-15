// n => matches.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {
public:
    vector<vector<int>>
    findWinners(vector<vector<int>>& matches) {
        // Hash table tracking count of lost matches per player
        unordered_map<int, int> nLostMatchesTbl;
        // Iterate over each match in the table
        for (auto & match : matches) {
            auto & winnerId = match[0];
            auto & loserId = match[1];
            
            // Update count of lost matches for loser
            nLostMatchesTbl[loserId]++;
            
            // Add the winner to the table if the no match has been
            // lost by the winner so far
            if (nLostMatchesTbl.find(winnerId) == nLostMatchesTbl.end()) {
                nLostMatchesTbl[winnerId] = 0;
            }
        }
        
        // Build list of only winners and single match losers
        vector<int> onlyWinnersV, singleMatchLosersV;
        for (auto & entry : nLostMatchesTbl) {
            auto & nLostMatches = entry.second;
            if (1 == nLostMatches) {
                singleMatchLosersV.emplace_back(entry.first);
            } else if (0 == nLostMatches) {
                onlyWinnersV.emplace_back(entry.first);
            }
        }
        
        // Arrange winners and single match losers in ascending order
        sort(onlyWinnersV.begin(), onlyWinnersV.end());
        sort(singleMatchLosersV.begin(), singleMatchLosersV.end());
        
        return vector<vector<int> >({onlyWinnersV, singleMatchLosersV});
    }
};
