// Time complexity : O(1)
// Space complexity : O(1)
class Solution {
public:
    int
    accountBalanceAfterPurchase(int purchaseAmount) {
        const int initialBankBalance = 100;
        if (0 == purchaseAmount % 10) {
            // Purchase amount is an exact multiple of 10. No adjustment reqd
            return initialBankBalance - purchaseAmount;
        }
        
        // Purchase amount is not an exact multiple of 10. Adjustment reqd
        // to nearest multiple
        int nearestUpperMultiple = 10 * ceil((float)purchaseAmount / 10);
        int nearestLowerMultiple = 10 * floor((float)purchaseAmount / 10);
        // Prefer rounding purchase amount to nearest upper multiple of 10
        // if both the upper and lower multiples are equidistant
        if (nearestUpperMultiple - purchaseAmount <= purchaseAmount - nearestLowerMultiple) {
            purchaseAmount = nearestUpperMultiple;
        } else {
            purchaseAmount = nearestLowerMultiple;
        }
        
        // Adjust bank balance to reflect purchase
        return initialBankBalance - purchaseAmount;
    }
};
