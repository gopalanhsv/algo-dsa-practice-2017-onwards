// Time complexity : O(logn)
// Space complexity : O(1)

class Solution {
public:
    int numberOfMatches(int n) {
        
        // Simulate the tournament
        int nTeams = n;
        int nMatches = 0;
        while (nTeams > 1) {
            if (0 == (nTeams & 0x1)) {
                // Even number of teams
                // Number of matches played is half the number of teams
                nMatches += (nTeams / 2);
                // Only winners(half the number of teams) advance to next round
                nTeams /= 2;
            } else {
                // Odd number of teams
                // One of the teams advances directly to next round (free ticket).
                // Rest of the teams play matches
                nMatches += ((nTeams - 1) / 2);
                // Winners also advance to next round along with the free ticket team
                nTeams = 1 + ((nTeams - 1) / 2);
            }
        }
        
        return nMatches;
    }
};
