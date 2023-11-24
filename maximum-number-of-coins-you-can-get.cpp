// n => piles.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)
class Solution {
public:
    int
    maxCoins(vector<int>& piles) {
        // Alice always gets the pile with max stones of triplets choosen,
        // X gets the 2nd max pile, while Bob always gets the pile with min stones
        // => To optimize the number of coins collected by X, adopt following
        // greedy approach to always maximise the 2nd max value while selecting
        // a triplet from the piles yet to be processed
        // => Select the max value for Alice, select 2nd max for X and
        // select the min val for Bob. Repeat this till all piles are exhausted
        
        // Sort the piles in non-increasing order
        sort(piles.begin(), piles.end(), greater<int>());
        // Determine number of pile triplets which will be selected
        auto nRemainingTriplets = piles.size() / 3;
        auto maxCoinsObtained = 0;
        // Tracks the index of the pile with max coins in next triplet to be selected
        auto maxPileIdx = 0;
        // Process for all triplets
        while (nRemainingTriplets > 0) {
            --nRemainingTriplets;
            // Coins from max pile go to Alice
            // Select coins from 2nd max pile for X
            maxCoinsObtained += piles[maxPileIdx + 1];
            // Coins from min pile go to Bob
            // Advance to next pile with max coins from amongst the remaining
            maxPileIdx += 2;
        }
        
        return maxCoinsObtained;
    }
};
