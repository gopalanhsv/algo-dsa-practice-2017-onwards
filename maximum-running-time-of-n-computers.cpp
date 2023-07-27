// x => battery life range for running the system [1, sum of all battery lifes]
// Time complexity : nlogx
// Space complexity : O(1)

class Solution {
public:
    long long
    maxRunTime(int n, vector<int>& batteries) {
    
        // Base case of lesser batteries than the number of computers
        if (n > batteries.size()) {
            return 0;
        }
        
        // Minimum time for which all the 'n' computers can run simultaneously
        // would be determined by the battery with least battery life
        // Maximum time for which all the 'n' computers can run simultaneously
        // would be at most the sum of all the battery lives/charge distributed
        // equally over each of the 'n' computers (i.e. totally energy in the
        // battery system being distributed equally amongst all 'n' comps)
        long long minBatteryLife = numeric_limits<long long>::max();
        long long batteryLifeSum = 0;
        for (auto & batteryLife : batteries) {
            minBatteryLife = min(minBatteryLife, (long long)batteryLife);
            batteryLifeSum += batteryLife;
        }
        
        long long minRunTime = minBatteryLife;
        long long maxRunTime = batteryLifeSum / n;
        
        // Execute a binary search in the closed range [minRunTime, maxRunTime]
        // to determine the max time all computers can be run simultaneously
        // using the given energy storage system
        long long l = minRunTime;
        long long r = maxRunTime;
        
        while (l < r) {
            // Doing the +1 stunt as l = mid setting is done below,
            // else search will get stuck in infinite loop
            long long mid = l + (r - l) / 2 + 1;
            if (possibleToOperate(n, batteries, mid)) {
                // Possible to run all the computers simultaneously for 'mid'
                // mins with given battery storage system => a lower bound for
                // the search range. Check if computers can be run simultaneously
                // for longer time in the upper part of search range
                l = mid;
            } else {
                // Not possible to run all the computers simultaneously for 'mid'
                // mins with given battery storage system => an upper bound for
                // the search range. Check if computers can be run simultaneously
                // for lesser time in the lower part of search range
                r = mid - 1;
            }
        }
        
        // Binary search terminates with l == r. The ends of the search
        // range converge towards each other in a pincer movement finally
        // ending at the max possible time for which all computers can be
        // run simultaneously
        return l;
    }
    
private:
    
    bool
    possibleToOperate(int n, vector<int>& batteries, long long reqdRunTime) {
        
        // Compute the total battery life(energy charge) required to run the
        // given number of computers for the required time
        long long totalBatteryChargeReqd = reqdRunTime * n;
        // Iterate over each battery in the storage system one by one; and 
        // use it to run the system of 'n' computers simultaneously for
        // the required run time
        for (auto & batteryLife : batteries) {
            // Using the current battery reduces the amount of charge
            // required to run the computer system by minimum of the
            // either the current battery life (battery cannot be used
            // beyond its life) OR required run time (a single battery 
            // wont be used beyond the specified computer system run time)
            totalBatteryChargeReqd -= min(reqdRunTime, (long long)batteryLife);
        }
        
        // After using up all the batteries as specified above, the amount of
        // energy/battery life needed to run the system for specified time 
        // should be not +ve (i.e. needing more energy)
        return totalBatteryChargeReqd <= 0;
    }
};
