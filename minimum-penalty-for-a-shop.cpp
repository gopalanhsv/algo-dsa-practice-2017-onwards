// n => customers.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    int
    bestClosingTime(string customers) {
        auto nHours = customers.size();
        // Shop closing times range is [0, nHours] commencing from 0 and 
        // including the last tick after the customer visit log at 'nHours'
        
        // postClosingPenaltyTbl[i] is penalty increment due to customers
        // turning up after/post the shop closing at hour 'i'
        vector<int> postClosingPenaltyTbl(nHours + 1, 0);
        auto nCustomersPostClosure = 0;
        // Iterate over the shop closing times from R->L sequentially
        for (int hrId = nHours - 1; hrId >= 0; --hrId) {
            // Shop closes at time 'hrId'
            // Update the number of customers who turn up post shop closure
            if (customers[hrId] == 'Y') {
                ++nCustomersPostClosure;
            }
            // Penalty would be the number of customers which turn up
            // after the shop closing
            postClosingPenaltyTbl[hrId] = nCustomersPostClosure;
        }

        // Tracks the minimum penalty for shop closure across all possible hours
        auto minPenalty = numeric_limits<int>::max();
        // Tracks the earliest shop closing time which result in min penalty
        auto earliestShopClosingTime = numeric_limits<int>::max();
        // Tracks the number of hours having no customers turning up prior to shop closure
        // Iterate over the shop closing times from L->R sequentially
        auto nHrsWithNoCustomersPreClosure = 0;
        for (auto hrId = 0; hrId <= nHours; ++hrId) {
            // Shop closes at time 'hrId'
            // Penalty would be the number of customers which turn up in [hrId, --]
            // plus the number of hours with no customers in [0, hrId - 1]
            auto totalPenalty =
                nHrsWithNoCustomersPreClosure + postClosingPenaltyTbl[hrId];
            // Update the min penalty and earliest time as which it is seen
            if (totalPenalty < minPenalty) {
                earliestShopClosingTime = hrId;
                minPenalty = totalPenalty;
            }
            
            // Update the number of hours with no customers who turn up prior
            // to shop closure
            if ((hrId < nHours) && (customers[hrId] == 'N')) {
                ++nHrsWithNoCustomersPreClosure;
            }
        }
        
        return earliestShopClosingTime;
    }
};
