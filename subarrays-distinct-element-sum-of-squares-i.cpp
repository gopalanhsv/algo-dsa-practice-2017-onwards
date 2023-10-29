// n => nums.size()
// Time complexity : O(n ^ 2)
// Space complexity : O(n)
class Solution {
public:
    int
    sumCounts(vector<int>& nums) {
        
        auto arrSz = nums.size();
        unordered_map<int, int> distinctElems2SubArrCntTbl;
        // Iterate over possible subarray start locations
        for (auto startIdx = 0; startIdx < arrSz; ++startIdx) {
            unordered_set<int> subArrElems;
            // Iterate over possible subarray end locations
            for (auto endIdx = startIdx; endIdx < arrSz; ++endIdx) {
                // Subarray extends over [startIdx, endIdx]
                subArrElems.insert(nums[endIdx]);
                // Distinct elems count within subarray
                auto nDistinctElems = subArrElems.size();
                // Update table tracking count of subarrays per number
                // of distinct elements per subarray
                distinctElems2SubArrCntTbl[nDistinctElems]++;
            }
        }
        
        // Compute sum of squares of num distinct elements for each subarray
        auto squaresSum = 0;
        for (auto & ent : distinctElems2SubArrCntTbl) {
            auto & nDistinctElems = ent.first;
            auto & subArrCnt = ent.second;
            squaresSum += (nDistinctElems * nDistinctElems) * subArrCnt;
        }
        return squaresSum;
    }
};
