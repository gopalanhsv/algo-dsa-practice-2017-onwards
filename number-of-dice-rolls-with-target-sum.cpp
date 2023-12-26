// d => num dice, f => num dice faces, t => target
// Time complexity : O(dft)
// Space complexity : O(dt)

class Solution {
public:
    int
    numRollsToTarget(int d, int f, int target) {
        // Let dpTbl[d][t] be the number of possible ways to get a target
        // sum 't' using a total of 'd' dice. Init the dpTbl with 0
        // as number of ways are yet to be computed
        vector<vector<int> > dpTbl(d + 1, vector<int>(target + 1, 0));
        const int moduloDivisor = 1000000000 + 7;
        
        // With a single dice, each of the target sums 1, 2, 3, .. f - 1, f can
        // be obtained in 1 way (i.e. top face of sole dice)
        for (auto tSum = 1; (tSum <= f) && (tSum <= target); ++tSum) {
            dpTbl[1][tSum] = 1;
        }

        // Increment by one dice at each step; compute the number of ways to
        // get all the (only) possible target sums (tSum) in range [1, target]
        // using any of the new dice with top face 'faceId' and remaining total
        // value of 'tSum - faceId' with all the earlier dice
        
        // Increment the number of dice at each step
        for (auto diceId = 2; diceId <= d; ++diceId) {
            // Iterate over all possible target sums
            for (auto tSum = 1; tSum <= target; ++tSum) {
                // Compute the number of ways to get target sum of 'tSum' 
                // using new dice 'diceId' and all earlier dice in range [1, diceId - 1]
                long nWays = 0;
                // Iterate over the possible contribution to sum 'tSum' which
                // is made by the dice 'diceId'. Can be any of its faces (top face)
                for (auto faceId = 1; faceId <= f; ++faceId) {
                    // Select only the feasible target sums
                    if (tSum >= faceId) {
                        nWays += dpTbl[diceId - 1][tSum - faceId];
                    }
                }
                dpTbl[diceId][tSum] = nWays % moduloDivisor;
            }
        }
        
        return dpTbl[d][target];
    }
};
