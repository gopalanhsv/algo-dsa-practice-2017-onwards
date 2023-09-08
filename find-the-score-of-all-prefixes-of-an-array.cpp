// Time complexity : O(nums.size()) / O(n)
// Space complexity : O(1)

class Solution {
public:
    vector<long long>
    findPrefixScore(vector<int>& nums) {
        int arrSz = nums.size();
        // Output array of score at each index
        vector<long long> scoresV(arrSz, 0);
        // Tracks the max array value seen so far
        int maxArrValSeen = 0;
        
        // Iterate over each array element sequentially from L->R
        for (auto idx = 0; idx < arrSz; ++idx) {
            auto & currElem = nums[idx];
            maxArrValSeen = max(maxArrValSeen, currElem);
            // Compute the value of conversion array at current index
            long long convArrValAtCurrIdx = currElem + maxArrValSeen;
            // Compute score array value at current index via prefix sum technique
            scoresV[idx] = convArrValAtCurrIdx;
            if (idx > 0) {
                scoresV[idx] += scoresV[idx - 1];
            }
        }
        return scoresV;
    }
};
