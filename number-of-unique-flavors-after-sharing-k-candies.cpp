// n => candies.size()
// Time Complexity : O(n)
// Space Complexity : O(n)

class Solution {
public:
    int
    shareCandies(vector<int>& candies, int k) {
        // Problem reduces to a fixed sized sliding window variant, wherein 
        // 'k' consecutive candies to be shared with the sister is represented
        // by a fixed sized sliding window of length 'k'
        // All that is required is to track the remaining candies available with
        // self (outside the window) using a hash table
        
        // Hash table tracking the candies outside the window
        // (flavor to count mapping)
        unordered_map<int, int> candiesTbl;
        auto nCandies = candies.size();
        for (auto i = 0; i != nCandies; ++i) {
            candiesTbl[candies[i]]++;
        }
        
        // Remove/give the first block of 'k' consecutive candies from the table
        for (auto winEnd = 0; winEnd < k; ++winEnd) {
            auto & flavor = candies[winEnd];
            if (--candiesTbl[flavor] == 0) {
                candiesTbl.erase(flavor);
            }
        }

        int maxUniqueFlavors = candiesTbl.size();
        // Iterate over the candies from L->R sequentially
        auto winStart = 0;
        for (auto winEnd = k; winEnd < nCandies; ++winEnd) {
            // Add new candy at right of window to be given away and grab back
            // the candy at start of window (shift the window to the right)
            auto flavor = candies[winEnd];
            if (--candiesTbl[flavor] == 0) {
                candiesTbl.erase(flavor);
            }
            flavor = candies[winStart++];
            candiesTbl[flavor]++;
            
            int nUniqueCandiesInHand = candiesTbl.size();
            maxUniqueFlavors = max(maxUniqueFlavors, nUniqueCandiesInHand);
        }
        return maxUniqueFlavors;
    }
};
