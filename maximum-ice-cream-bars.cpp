class Solution {
public:
    int
    maxIceCream(vector<int>& costs, int coins) {
        // To buy the maximum number of ice-cream bars with a given
        // amount of money; one should adopt the greedy approach of
        // always choosing the bars with least cost prior to picking
        // up those with higher cost
        
        // Adopt the greedy approach of always buying the bars having the
        // least cost (from the set of bars yet to bought) using the
        // remaining amount of money; till the money gets exhausted
        
        // Sort the ice-cream bars in the ascending order of costs
        // (for buying the least cost bar from amongst the remaining bars
        // at any point in time)
        sort(costs.begin(), costs.end());

        auto nBoughtBars = 0;
        auto nRemainingCoins = coins;
        // Iterate over the bars in the ascending order of their costs
        for (auto & cost : costs) {
            if (nRemainingCoins < cost) {
                // Insufficent money to buy bars from current bar onwards
                break;
            }
            // Buy the current bar and pay for it
            ++nBoughtBars;
            nRemainingCoins -= cost;
        }
        
        return nBoughtBars;
    }
};
