class Solution {
    
public:
    
    int
    maxProfit(vector<int>& prices) {
        //return maxProfitApproachOrderN(prices);
        return maxProfitApproachOrderN2(prices);
    }
    
private:
    
    int
    maxProfitApproachOrderN(vector<int>& prices) {

        int nPrices = prices.size();
        
        // Need a minimum of 2 days to have at least 1 buy-sell
        if (nPrices < 2) {
            return 0;
        }
        
        return 0;
    }
    
    
    int
    maxProfitApproachOrderN2(vector<int>& prices) {

        int nPrices = prices.size();
        
        if (nPrices < 2) {
            // Single/no trading days
            return 0;
        }
        
        // maxProfitV[x] represents the maximum possible profit
        // which can  be made by buy/sell with 1 day cooldown
        // in the closed range [0, x] days
        vector<int> maxProfitV(nPrices, 0);
        
        // Max possible profit made in range [0, 0]
        maxProfitV[0] = 0;
        // Max possible profit made in range [0, 1]
        maxProfitV[1] = max(0, prices[1] - prices[0]);
        
        // Iterate over the each of the prices/days sequentially and
        // compute the maximum possible profit which can be made for
        // at each of the day ranges [0, d]
        for (int d = 2; d < nPrices; ++d) {
            
            // Compute max possible which can be made by selling on
            // the current day 'd' (if feasible)
            int maxProfitForSellOnThisDay = 0;
            for (int bd = d - 1; bd >= 0; --bd) {
                
                if (prices[d] <= prices[bd]) {
                    continue;
                }

                int profit = prices[d] - prices[bd];
                if (bd >= 2) {
                    profit += maxProfitV[bd - 2];
                } 
                
                maxProfitForSellOnThisDay =
                    max(maxProfitForSellOnThisDay, profit);
            }
            
            // Max profit possible over day range [0, d] if no
            // sale permitted on last/current day 'd'
            int maxProfitForNoSellOnThisDay = maxProfitV[d - 1];
            // Update max profit which can be made over the
            // day range [0, d]
            maxProfitV[d] =
                max(maxProfitForSellOnThisDay, maxProfitForNoSellOnThisDay);
        }
        
        return maxProfitV[nPrices - 1];
    }

};
