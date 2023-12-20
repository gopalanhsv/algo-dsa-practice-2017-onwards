// Time complexity : O(prices.size())
// Space complexity : O(1)
class Solution {
public:
    int 
    buyChoco(vector<int>& prices, int money) {
        // To minimize the spend on the chocolates, select 2 of the
        // least priced chocos (i.e first and second min)
        auto firstMin = numeric_limits<int>::max();
        auto secondMin = numeric_limits<int>::max();
        for (auto & price : prices) {
            if (price <= firstMin) {
                secondMin = firstMin;
                firstMin = price;
            } else if (price < secondMin) {
                secondMin = price;
            }
        }
        
        // Compute leftover money
        auto leftover = money - (firstMin + secondMin);
        // Leftover leading to debt => no buy possible
        return (leftover < 0) ? money : leftover;
    }
};
