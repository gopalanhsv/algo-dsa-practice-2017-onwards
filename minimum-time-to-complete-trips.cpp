// Time complexity : O(log (totalTrips x max(trip times)) )
// Space complexity : O(1)

class Solution {
public:
    long long
    minimumTime(vector<int>& time, int totalTrips) {
    
        // Upper bound on time taken to finish 'totalTrips' by all buses
        // would be dependent on the time taken by slowest bus
        // Lower bound on trip time to finish 'totalTrips' by all buses
        // would be the time taken by the fastest bus to complete 1 trip
        int slowestTripTime = 1;
        int fastestTripTime = numeric_limits<int>::max();
        for (auto & busTripTime : time) {
            slowestTripTime = max(slowestTripTime, busTripTime);
            fastestTripTime = min(fastestTripTime, busTripTime);
        }
        long long maxTripTime = totalTrips * (long long) slowestTripTime;
        long long minTripTime = (long long) fastestTripTime;
        
        // Execute a binary search in the range [minTripTime, maxTripTime]
        // to find the minimum time in which required number of 'totalTrips'
        // trips can be done
        long long l = minTripTime, r = maxTripTime;
        while (l < r) {
            long long mid = l + (r - l) / 2;
            if (canReqdNumTripsBeCompleted(time, mid, totalTrips)) {
                // Required number of 'totalTrips' trips can be completed by
                // the buses in time 'mid'. So this time becomes an upper
                // bound on the time required for given number of trip completions.
                // Check if possible to complete required number of trips
                // in lesser time.
                r = mid;
            } else {
                // Required number of 'totalTrips' trips cannot be completed by
                // the buses in time 'mid'. So this time becomes a lower
                // bound on the time required for given number of trip completions.
                // Check if possible to complete required number of trips
                // with more time.
                l = mid + 1;
            }
        }
        
        
        return l;
    }
    
private:
    
    bool
    canReqdNumTripsBeCompleted(vector<int>& tripTimesV,
                               long long time, int totalTrips) {
        long long nTotalTrips = 0;
        // Iterate over per trip time for each bus
        for (auto & tripTime : tripTimesV) {
            // Compute number of trips which can be done by this bus in
            // given amount of time. Add it to the total number of trips done
            nTotalTrips += (time / tripTime);
            // Adding code for time optimization below
            if (nTotalTrips >= totalTrips) {
                break;
            }
        }
        
        // Return true if total number of trips which can be done in
        // given time by all the buses is more than required
        return nTotalTrips >= totalTrips;
    }
    
};
