// Time complexity : O(num turns)
// Space complexity : O(1)

class Solution {
public:
    int
    isWinner(vector<int>& player1, vector<int>& player2) {
        int nTurns = player1.size();
        
        // Scores initialized in 1st turn
        int player1Score = player1[0]; 
        int player2Score = player2[0];
        // Scores updated for 2nd turn
        if (nTurns > 1) {
            player1Score += player1[1]; 
            player2Score += player2[1];
            if (player1[0] == 10) {
                // 10 hit by player1 in one of previous two turns
                // 2x hits for player1
                player1Score += player1[1]; 
            }
            if (player2[0] == 10) {
                // 10 hit by player2 in one of previous two turns
                // 2x hits for player1
                player2Score += player2[1]; 
            }
        }
        
        // Turn 3 onwards
        for (int i = 2; i < nTurns; ++i) {
            // Update score with hits for current turn
            
            if ((player1[i - 2] == 10) || 
                (player1[i - 1] == 10) ) {
                // 10 hit by player1 in one of previous two turns
                // 2x hits for player1
                player1Score += (player1[i] << 1); 
            } else {
                // No 10 hit by player1 in one of previous two turns
                // x hits for player1
                player1Score += player1[i]; 
            }
            
            if ((player2[i - 2] == 10) || 
                (player2[i - 1] == 10) ) {
                // 10 hit by player2 in one of previous two turns
                // 2x hits for player2
                player2Score += (player2[i] << 1); 
            } else {
                // No 10 hit by player2 in one of previous two turns
                // x hits for player2
                player2Score += player2[i]; 
            }
        }
        
        if (player1Score == player2Score) {
            // Draw
            return 0;
        }
        
        return (player1Score > player2Score) ? 1 : 2;
    }
};
