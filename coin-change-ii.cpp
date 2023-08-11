// A => amount, n => coins.size()
// Time complexity : O(nA)
// Space complexity : O(A)
class Solution {
public:
    int
    change(int amount, vector<int>& coins) {
        if (0 == amount) {
            // Base case of 0 amount => empty set of coins => 1 way
            return 1;
        }
        
        // Explore the numbers of ways to construct all possible amounts 
        // from 1 to 'amount' using the given coins via DP
        return coinChangeBottomUpDP(amount, coins);
    }
    
private:
    
    int
    coinChangeBottomUpDP(int amount, vector<int>& coins) {
        // nCombinationsTbl[x] is the number of coin combinations using coins from the
        // array 'coins' that make up the amount 'x'
        vector<long> nCombinationsTbl(amount + 1, 0);

        // Iterate over all the coins (Not having 'amount' in the out loop with 'coins'
        // in inner loop as it leads to incorrect results due to the same combination
        // of coin vals being counted multiple/duplicate times)
        for (auto & coinVal : coins) {
            if (coinVal > amount)  {
                // Target amount val is exceeded by the current coin => current coin
                // cannot be used to build up the 'amount'
                continue;
            }
            
            // Target amount corresponding to current coin val can be built
            // using the current coin
            nCombinationsTbl[coinVal] += 1;
            // Determine the number of combinations to construct all amounts in the
            // range [1, amount] using current coin and the coins seen so far
            // Iterate over all amounts which can be built using the current coin
            for (auto currentAmt = coinVal + 1; currentAmt <= amount; ++currentAmt) {
                // Compute the amount from current amount which remains after using an
                // instance of the current coin
                auto remainderAmt = currentAmt - coinVal;
                // Current amount can be constructed using 1 current coin along with 
                // some/all seen coins using as many combinations as the remainder amount
                nCombinationsTbl[currentAmt] += nCombinationsTbl[remainderAmt];
            }
        }
        
        return nCombinationsTbl[amount];
    }
};
