// Time complexity : O(n)
// Space complexity : O(n)
class Solution {
public:
    vector<int>
    circularGameLosers(int n, int k) {
        // Ball received status for each player
        // ballRxedV[i] = true => player 'i' has rxed ball
        // ballRxedV[i] = false => player 'i' has not rxed ball
        vector<bool> ballRxedV(n, false);
        
        // Simulate the game (0-indexed players)
        int playerId = 0;
        long long turnId = 1;
        // Keep player the game till a player who has rxed ball earlier gets it again
        while (!ballRxedV[playerId]) {
            // Update that player has received the ball
            ballRxedV[playerId] = true;
            // Compute the player who get the ball in the next turn
            long long nSteps = (turnId * k) % n;
            auto nextPlayerId = (playerId + nSteps) % n;
            playerId = nextPlayerId;
            // Update turn id for next turn
            ++turnId;
        }
        
        // Determine the list of losers (1-index)
        vector<int> losersV;
        for (auto pId = 0; pId != n; ++pId) {
            if (!ballRxedV[pId]) {
                // Add 1-indexed id of loser
                losersV.emplace_back(pId + 1);
            }
        }
        
        return losersV;
    }
};
