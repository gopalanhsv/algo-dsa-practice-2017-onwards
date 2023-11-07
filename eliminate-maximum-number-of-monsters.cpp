// n => dist.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    int
    eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        
        // Copute the time at which the monsters reach the city
        int nMonsters = dist.size();
        vector<double> arrivalTimeV(nMonsters);
        for (int i = 0; i != nMonsters; ++i) {
            arrivalTimeV[i] = double(dist[i]) / speed[i];
        }
        
        // Adopt greedy approach of eliminating the closest monster alive
        // and nearest too city from amongst the remaining monsters 
        // Sort the arrival times in ascending order
        sort(arrivalTimeV.begin(), arrivalTimeV.end());

        // Iterate over the arrival times of monsters in ascending order, eliminating
        // them one by one till game is lost or all monsters are eliminated
        
        // Start by eliminating closest monster as weapon fully charged
        int nMonstersEliminated = 1;
        double minTimeToChargeWeaponAfterUse = 1.0;
        double currTime = 0.0;
        int monsterIdx = 1;
        while (monsterIdx < nMonsters) {
            // Recharge weapon
            currTime += minTimeToChargeWeaponAfterUse;
            // Attempt to eliminate monster closest to city
            if (currTime < arrivalTimeV[monsterIdx++]) {
                // Eliminate closest alive monster with recharged weapon
                ++nMonstersEliminated;
            } else {
                // Game lost as closest monster arrives prior to weapon recharge
                break;
            }     
        }
        
        return nMonstersEliminated;
    }
};
