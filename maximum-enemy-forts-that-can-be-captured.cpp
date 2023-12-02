// n => forts.size()
// Time complexity : O(n)
// Time complexity : O(1)

class Solution {
public:
    int
    captureForts(vector<int>& forts) {
        auto nForts = forts.size();
        
        int nMaxFortsCaptured = 0;
        
        // Iterate over the forts from L->R
        // Tracks the location of closest fort housing army/empty forts
        // to left with only intervening empty forts
        int nClosestArmyFortToLeft = -1;
        int nClosestEmptyFortToLeft = -1;
        for (auto i = 0; i < nForts; ++i) {
            auto & fort = forts[i];
            if (1 == fort) {
                // Current fort is an Army fort
                if (-1 != nClosestEmptyFortToLeft) {
                    // Capture all enemy forts between current and closest
                    // empty fort to the left
                    auto nFortsCaptured = (i - nClosestEmptyFortToLeft - 1);
                    nMaxFortsCaptured =
                        max(nMaxFortsCaptured, nFortsCaptured);
                }
                // Update location of closest army and empty forts
                nClosestArmyFortToLeft = i;
                nClosestEmptyFortToLeft = -1;
            } else if (-1 == fort) {
                // Current fort is an Empty fort
                if (-1 != nClosestArmyFortToLeft) {
                    // Capture all enemy forts between current and closest
                    // army fort to the left
                    auto nFortsCaptured = (i - nClosestArmyFortToLeft - 1);
                    nMaxFortsCaptured =
                        max(nMaxFortsCaptured, nFortsCaptured);
                }
                // Update location of closest army and empty forts
                nClosestArmyFortToLeft = -1;
                nClosestEmptyFortToLeft = i;
            }
        }
        return nMaxFortsCaptured;
    }
};
