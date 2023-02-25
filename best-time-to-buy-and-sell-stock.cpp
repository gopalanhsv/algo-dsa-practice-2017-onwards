class Solution {
public:
    int
    maxProfit(vector<int>& prices) {
        int minCostPriceSeenSoFar = prices[0];
        int maxProfit = 0;
        int n = prices.size();
        for (int i = 1; i != n; ++i) {
            auto & p = prices[i];
            // Compute the maximum profit if stock is sold today;
            // for max profit on sale today, stock should have been
            // bought at minimum prices amongst all of the earlier days
            
            // Update min cost price seen so far and max profit possible
            // to include the transaction done today
            maxProfit = max(maxProfit, p - minCostPriceSeenSoFar);
            minCostPriceSeenSoFar = min(minCostPriceSeenSoFar, p);
        }
        return maxProfit;
    }
};
