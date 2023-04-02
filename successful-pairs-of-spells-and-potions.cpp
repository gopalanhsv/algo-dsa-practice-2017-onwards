// Time complexity
// O((spells.size()) X log (potions.size()))
// Space complexity
// O(log (potions.size()))

class Solution {
public:
    vector<int>
    successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        
        // Since spell+potion pair is considered a success if the product of
        // their respective strengths is g.e the value of 'success', for a particular
        // spell with strength 'ss', all potions with strengths 'ps' s.t 
        // ss X ps >= success are 'successful pairs'; i.e
        // all potions with strengths 'ps' s.t ps >= success / ss
        // To efficiently find the number of potions satisfying the above criterion,
        // sort the potions in the non-decreasing order of their respective strengths
        // and locate the leftmost potion with the smallest strength satisfying the above
        // criterion. All potions located to the right of the lcoated potion will
        // have same/more strength and will automatically become successful pairs
        int nSpells = spells.size();
        vector<int> successfulPairsV(nSpells, 0);
        
        // Sort the portions in non-decreasing order of respective strengths
        sort(potions.begin(), potions.end());
        
        int nPotions = potions.size();
        int nSuccessfulPairs = 0;
        // Iterate over each spell in sequence
        for (int i = 0; i != nSpells; ++i) {
            auto & spellStrength = spells[i];
            // Compute the min required potion strength for the
            // current spell to be successful
            long long minPotionStrengthReqd = (success + spellStrength - 1)/ spellStrength;
            // Locate the leftmost potion with the min required strength via binary search
            auto iter = lower_bound(potions.begin(), potions.end(), minPotionStrengthReqd);
            // Copute the number of potions which will form a successful pair with current spell
            int nPotionsWithReqdStrength = potions.end() - iter;
            successfulPairsV[i] = nPotionsWithReqdStrength;
        }
        
        return successfulPairsV;
    }
};
