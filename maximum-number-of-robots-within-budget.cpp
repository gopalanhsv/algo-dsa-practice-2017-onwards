// Time complexity : O(nlogn) n => number of robots
// Space complexity : O(n)

class Solution {
public:
    int
    maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget) {
    
        // Problem requires selection of 'k' consecutive robots; tracking the maximum of
        // the charge times amongst the selected block; and sum of running costs of robots
        // in the selected block
        
        // 1. Use a variable sized sliding window to select the set of consecutive robots
        // 2. Use an indexed priority queue (max heap) to track the robot with the maximum
        //    'charge time' within the sliding window of consecutive robots. Using an
        //    indexed PQ as multiple robots may have same charge times and one needs to
        //    delete the charge time entry for robots at left side/start of window when
        //    budget gets exceeded and robots at left/start of window have to be discarded
        // 3. Use a prefix sum array over running costs to quickly compute the sum of the
        //    selected 'k' consnecutive robots
        
        int nRobots = chargeTimes.size();
        // Tracks the sum of running costs of selected robots/those within the
        // sliding window
        long long sumOfRunCostsOfSelectedRobots = 0;
        // Indexed priority queue - Table tracking the charge times of
        // consecutive robots within the sliding window (i.e. selected robots)
        map<int, int, greater<int> > sWinChargeTimesTbl;
        
        // Start of window
        int sWinStart = 0;
        // Tracks the max number of robots which can be selected
        int maxRobots = 0;
        
        // Keep on adding/selecting robots at the end/right of the sliding
        // window sequentially by extending the window
        for (int sWinEnd = 0; sWinEnd != nRobots; ++sWinEnd) {
            // Cost params for current robot at end of window
            auto & currRunCost = runningCosts[sWinEnd];
            auto & currChargeTime = chargeTimes[sWinEnd];
            
            // Select/add the current robot to the set of consecutive robots
            sumOfRunCostsOfSelectedRobots += currRunCost;
            sWinChargeTimesTbl[currChargeTime] += 1;
        
            // Update the number of robots in the window and compute the
            // time for running the robots selected in the window
            long long nSelectedRobots = sWinEnd - sWinStart + 1;
            long long chargeTimesContrib = ((sWinChargeTimesTbl.begin())->first);
            long long runCostsContrib = nSelectedRobots * sumOfRunCostsOfSelectedRobots;            
            long long totalCost = chargeTimesContrib + runCostsContrib;
            
            // Till the running cost of selected robots in the window exceeds
            // given budget, remove previously selected robots one by one from
            // the window left till cost is satisfied by budget
            while ((totalCost > budget) && (sWinStart <= sWinEnd)) {
                
                // Remove/Deselect the robot at start of window
                auto chargeTimeAtWinStart = chargeTimes[sWinStart];
                if (--sWinChargeTimesTbl[chargeTimeAtWinStart] == 0) {
                    sWinChargeTimesTbl.erase(chargeTimeAtWinStart);
                }
                sumOfRunCostsOfSelectedRobots -= runningCosts[sWinStart];
                // Advance the window start
                ++sWinStart;
                
                --nSelectedRobots;
                if (nSelectedRobots > 0) {
                    // Update the running cost for the set of selected robots
                    chargeTimesContrib = ((sWinChargeTimesTbl.begin())->first);
                    runCostsContrib = nSelectedRobots * sumOfRunCostsOfSelectedRobots; 
                    totalCost = chargeTimesContrib + runCostsContrib;
                }
            }
            
            // Update the maximum number of selected robots
            maxRobots = max(maxRobots, (int) nSelectedRobots);
        }

        return maxRobots;
    }
};
