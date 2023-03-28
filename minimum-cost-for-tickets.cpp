// Time complexity
// O(max value in days array)
// Space complexity
// O(max value in days array)

class Solution {
public:
    int
    mincostTickets(vector<int>& days, vector<int>& costs) {
        // Let dpTbl[i] be the min cost to travel for the first
        // 'i' days (inclusive of the ith day) using any of the
        // 1/7/30 day passes in combination
        int lastTravelDay = days[days.size() - 1];
        vector<int> dpTbl(lastTravelDay + 1, 0);

        // Iterate over all travel days sequentially
        // For each travel day 'x', find the minimum cost to travel
        // from 1st travel day upto and inclusive till the day 'x'
        // using all possible combo of 1/7/30 day passes
        int nTravelDays = days.size();
        for (int i = 0; i < nTravelDays; ++i) {
            
            int currDay = days[i];
            
            // Minimum cost to travel upto current day from
            // 1st day; with current day travel using 1 day pass
            // (current day travel will be the last day of 1 day pass)
            int minCostUptoCurrDayWith1DayPass = 
                costs[0] + dpTbl[max(0, currDay - 1)];
            // Minimum cost to travel upto current day from
            // 1st day; with current day travel using 7 day pass
            // (current day travel will be the last day of 7 day pass)
            int minCostUptoCurrDayWith7DayPass = 
                costs[1] + dpTbl[max(0, currDay - 7)];
            // Minimum cost to travel upto current day from
            // 1st day; with current day travel using 30 day pass
            // (current day travel will be the last day of 30 day pass)
            int minCostUptoCurrDayWith30DayPass = 
                costs[2] + dpTbl[max(0, currDay - 30)];
            
            // Minimum cost to travel upto current day is the minimum
            // of the above three computed costs using 1/7/30 day pass
            dpTbl[currDay] =
                min(min(minCostUptoCurrDayWith1DayPass, minCostUptoCurrDayWith7DayPass),
                    minCostUptoCurrDayWith30DayPass);
            
            // Above computed cost of travel is set for all days upto
            // (but not including) next travel day; to make the dp computation
            // seamless without gaps in between/avoid a binary search for closest
            // actual prior travel days at current day - 1/7/30
            if (i < nTravelDays - 1) {
                auto & nextTravelDay = days[i + 1];
                for (int td = currDay + 1; td < nextTravelDay; ++td) {
                    dpTbl[td] = dpTbl[currDay];
                }
            }
        }
        
        return dpTbl[lastTravelDay];
    }
};
