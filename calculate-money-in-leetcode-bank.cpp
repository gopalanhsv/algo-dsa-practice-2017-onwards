// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    int
    totalMoney(int n) {
        // Number of complete weeks in which gets deposited
        auto nWeeks = n / 7;
        
        // Compute total amount deposited during all full day weeks
        long amtDepositedFirstWeek = (1 + 7) * 7 / 2;
        
        // 1st week = 1 2 3 4 5 6 7  = FwAmt
        // 2nd week = 2 3 4 5 6 7 8  = FwAmt + 7
        // 3rd week = 3 4 5 6 7 8 9  = FwAmt + 14
        // 4th week = 4 5 6 7 8 9 10 = FwAmt + 21
        // wth week = i ...... i + 6 = FwAmt + 7 * (w - 1)
        // Totals for each week form an Arithmetic Progression
        // => Total sum for 'w' complete weeks 
        // = (w * (First Week Amt + Last Week Amt) / 2) 
        // = (w * (FwAmt + FwAmt + 7 *( w - 1 )) / 2)
        // = (w * FwAmt) + (7w(w - 1)/2)
        
        long totalAmt = 0;
        if (nWeeks > 0) {
            totalAmt = 
                ((nWeeks * amtDepositedFirstWeek) + (nWeeks * (7 * (nWeeks - 1)) / 2) );
        }
        
        // Days to be accounted for in last incomplete week
        auto nDays = n % 7;
        
        // Add the amount deposited in the days of last week
        long startAmtForLastWeek = nWeeks + 1;
        for (auto i = 0; i != nDays; ++i) {
            totalAmt += (startAmtForLastWeek + i);
        }
        
        return totalAmt;
    }
};
