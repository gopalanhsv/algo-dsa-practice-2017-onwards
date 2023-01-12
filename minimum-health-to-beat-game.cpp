class Solution {
public:
    long long
    minimumHealth(vector<int>& damage, int armor) {
        // In the absence of any armor, the minimum health required
        // to complete the game would the sum of damages at all levels
        // plus 1 (to avoid health dropping to/below 0 at any level)
        
        // For the optimum effective use of armor, it must be
        // employed at the location of maximum damage (greedy
        // approach)
        
        long long minReqdHealth = 1;
        int maxDamageSeen = numeric_limits<int>::min();
        for (auto & lvlDamage : damage) {
            minReqdHealth += lvlDamage;
            maxDamageSeen = max(maxDamageSeen, lvlDamage);
        }
        
        // Maximum amount of damage which can be deflected by armor
        // at the location of level with max damage
        int damageNeutralizeByArmor = min(maxDamageSeen, armor);
        
        // Account for the damage deflected by armor
        minReqdHealth -= damageNeutralizeByArmor;
        
        return minReqdHealth;
    }
};
