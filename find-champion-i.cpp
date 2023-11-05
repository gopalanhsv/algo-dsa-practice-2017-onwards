// n => grid.size()
// Time complexity : O(n ^ 2)
// Space complexity : O(1)
class Solution {
public:
    int
    findChampion(vector<vector<int>>& grid) {
        // Team 'x' will be the champion if it is stronger than
        // all other teams 'y'
        // => grid[x][y] = 1 for all y != x;
        // => all cols for row 'x' should be 1 except for col 'x'
        auto nTeams = grid.size();
        
        // Iterate over each team
        for (auto teamId = 0; teamId < nTeams; ++teamId) {
            bool isChampion = true;
            // Iterate over other teams
            for (auto otherTeamId = 0; otherTeamId < nTeams; ++otherTeamId) {
                if ((otherTeamId != teamId) && (!grid[teamId][otherTeamId])) {
                    // Current 'teamId' does not dominated other team 'otherTeamId'
                    // => it is not a champion
                    isChampion = false;
                    break;
                }
            }
            
            if (isChampion) {
                // Current team dominates all other teams
                return teamId;
            }
        }
        
        // Erron => No dominant team
        return -1;
    }
};
