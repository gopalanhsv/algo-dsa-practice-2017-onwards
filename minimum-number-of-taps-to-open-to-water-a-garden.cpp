class Solution {
public:
    int
    minTaps(int n, vector<int>& ranges) {
    
        // Iterate through all tap ranges and convert all the ranges to intervals.
        // Also normalize all ranges s.t any interval extending below 0 is set to 0
        // and any intervals above n is marked as n, since we are interested only in
        // the interval [0, n] for watering
        vector<pair<int, int> > wateringIntervalsV;
        for (int i = 0 ; i != ranges.size(); ++i) { // tr =>tap range
            if (ranges[i] == 0) {
                continue; // Skip zero range taps
            }
            int lo = max(0, i - ranges[i]);
            int hi = min(n, i + ranges[i]);
            wateringIntervalsV.emplace_back(pair<int, int>({lo, hi}));
        }
        
        // All of taps have zero range, so no watering possible
        if (wateringIntervalsV.size() == 0) {
            return -1;
        }
        
        // To water the entire garden with the minimum number of taps,
        // we should take the greedy approach of first selecting tap which
        // waters the widest interval range possible, eliminate the other
        // taps whose range is encompassed wholly by this tap; then again
        // select the tap watering the widest interval range possible from
        // remaining taps and so on. At each point we are trying to water
        // max portion of garden with a single tap, so this will lead to
        // minimum number of taps required overall
        
        // Sort the watering interval ranges in the ascending order of
        // their start locations 
        struct TapWateringRangeIntervalCmpObj {
            bool
            operator()(const pair<int, int>& i1, const pair<int, int>& i2) {
                if (i1.first == i2.first) {
                    return i1.second > i2.second;
                }
                return i1.first < i2.first;
            }
        };
        sort(wateringIntervalsV.begin(), wateringIntervalsV.end(),
             TapWateringRangeIntervalCmpObj());
        
        // If the first watering interval ordered as per start locations
        // doesn't commence at/water point index 0, then its is not
        // possible to water entire range [0 - n]
        if (wateringIntervalsV[0].first > 0) {
            return -1;
        }
        
        // Iterate over the water range intervals in the ascending order of
        // start points
        int minTaps = 0;
        int wiIdx = 0;
        int currIntervalEnd = wateringIntervalsV[wiIdx].second;
        while (wiIdx != wateringIntervalsV.size()) {
            // Current watering interval is selected (requires a new tap)
            ++minTaps;
            
            currIntervalEnd = 
                max(currIntervalEnd, wateringIntervalsV[wiIdx].second);
            
            // If current watering interval endpoint reaches the right of
            // watering range, no more taps required
            if (currIntervalEnd == n) {
                return minTaps;
            }
            
            // Skip all watering intervals ranges which overlap with current
            // selected interval, except the one which extends the most beyond
            // the right end point of the current interval or commences at
            // the right endpoint. That unskipped watering interval
            // range is made the current interval for next iteration
            int nextIntervalEnd = currIntervalEnd;
            int j = wiIdx;
            while (j + 1 != wateringIntervalsV.size() && 
                   wateringIntervalsV[j + 1].first <= currIntervalEnd) {
                nextIntervalEnd = max(wateringIntervalsV[j + 1].second, nextIntervalEnd);
                ++j;
            }
            
            if (j == wiIdx) {
                break;
            }

            // Advance to next watering interval range
            wiIdx = j;
            currIntervalEnd = nextIntervalEnd;
        }
        
        return -1;
        
    }
};
