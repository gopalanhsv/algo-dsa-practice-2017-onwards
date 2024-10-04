// n => skill.size()
// Time Complexity : O(nlogn)
// Space Complexity : O(n)
class Solution {
public:
    long long
    dividePlayers(vector<int>& skill) {
        int nPlayers = skill.size();
        // Sort the players in non decreasing order
        sort(skill.begin(), skill.end());
        
        // Requirement of each team to have identical total skill
        // => teams of two members each can be formed only by selecting
        // 2 members having the highest and the lowest skill from amongst
        // those which have yet to be assigned to teams
        int lo = 0, hi = nPlayers - 1;
        int readTeamSkill = skill[lo] + skill[hi];
        long long totalChemistry = skill[lo] * skill[hi];
        ++lo, --hi;
        while (lo < hi) {
            int currentTeamSkill = skill[lo] + skill[hi];
            if (currentTeamSkill != readTeamSkill) {
                return -1;
            }
            long long currentTeamChemisty = skill[lo] * skill[hi];
            totalChemistry += currentTeamChemisty;
            ++lo, --hi;
        }
        
        return totalChemistry;
    }
};
