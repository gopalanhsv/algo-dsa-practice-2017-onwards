// n => prices.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    long long
    getDescentPeriods(vector<int>& prices) {
        
        long long totalPeriods = 0;
        int startDay;
        auto nDays = prices.size();
        // Iterate over each day from L->R sequentially
        for (auto dayId = 0; dayId < nDays; ++dayId) {
            // Compute duration of longest smooth descent period ending on the current day
            long long longestPeriodDuration = 1;
            if ((dayId > 0) && (prices[dayId - 1] - prices[dayId] == 1)) {
                // Current day price forms a smooth descent with previous day price
                longestPeriodDuration = dayId - startDay + 1;
            } else {
                // Current day price breaks any smooth descent with prices from previous day
                // Commence a new smoooth descent period here
                longestPeriodDuration = 1;
                startDay = dayId;
            }
            // Compute the number of smooth descent periods ending on the current day 'dayId'
            // Say 'longestPeriodDuration' => lpd. Then we get smooth descent periods as
            // [dayId, dayId], [dayId - 1, dayId], [dayId - 2, dayId],
            // [dayId - 3, dayId], [dayId - 4, dayId]...., [dayId - lpd + 1, dayId]
            // => 'lpd' smooth descent periods
            long long nPeriods = longestPeriodDuration;
            
            // Update the total number of seen long descent periods
            totalPeriods += nPeriods;
        }
        
        return totalPeriods;
    }
};
