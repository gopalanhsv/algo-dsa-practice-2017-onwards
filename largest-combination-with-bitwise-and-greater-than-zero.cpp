// n => candidates.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    int
    largestCombination(vector<int>& candidates) {
        const int nBitsInIntType = 8 * sizeof(int);
        vector<int> numCombinationsV(nBitsInIntType, 0);
        for (auto setBitPos = 0; setBitPos < nBitsInIntType; ++setBitPos) {
            int mask = (1 << setBitPos);
            for (auto & candidate : candidates) {
                if (mask & candidate) {
                    ++numCombinationsV[setBitPos];
                }
            }
        }
        
        int maxCombinationSize = 0;
        for (auto setBitPos = 0; setBitPos < nBitsInIntType; ++setBitPos) {
            maxCombinationSize = max(maxCombinationSize, numCombinationsV[setBitPos]);
        }

        return maxCombinationSize;
    }
};
