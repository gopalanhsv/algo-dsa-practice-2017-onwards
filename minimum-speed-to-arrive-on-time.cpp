// n => dist.size()
// x => range of possible speeds {maxSpeed - minSpeed}
// Time complexity : O(nlogx)
// Space complexity : O(1)

class Solution {
public:
    int
    minSpeedOnTime(vector<int>& dist, double hour) {
    
        int maxSpeed = 10000000; // from prob definition
        int minSpeed = 1; // smallest +ve integer
    
        if (!validSpeed(dist, hour, maxSpeed)) {
            // Not possible to reach office at max allowed speed
            return -1;
        }
        
        // Exec binary search to determine the minimum speed in the range
        // [minSpeed, maxSpeed] which allows the commuter to reach destination
        // within the allotted time as per input constraints
        int lo = minSpeed;
        int hi = maxSpeed;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (validSpeed(dist, hour, mid)) {
                // Commute possible at 'mid' speed. Attempt
                // to search for a lesser speed to left of mid
                hi = mid;
            } else {
                // Commute not possible at 'mid' speed. Search
                // for a higher possible commute speed
                lo = mid + 1;
            }
        }
        
        // Search terminates at lo = hi
        return lo;
    }

private:
     
    bool
    validSpeed(vector<int>& dist, double & hour, int speed) {
        // Checks whether it is possible to reach office within alloted time; catching each
        // new train in sequential order travelling at given speed at appropriate 1 hour marks
        double totalCommuteTime = 0;
        for (auto & d : dist) {
            double commuteTimeInCurrTrain = (double)d / speed;
            
            if (totalCommuteTime + commuteTimeInCurrTrain > hour) {
                return false;
            }
            
            // Adjust current commute to to commence subsequent train journey
            // at next immediate 1 hour mark
            totalCommuteTime += ceil(commuteTimeInCurrTrain);
        }
        
        return true;
    }
};
