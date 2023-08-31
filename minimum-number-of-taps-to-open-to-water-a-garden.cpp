// n => ranges.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {
public:
    int
    minTaps(int n, vector<int>& ranges) {
    
        // Iterate through all tap ranges and convert all the ranges to intervals.
        // Since we are interested only in the interval [0, n] for watering, normalize
        // all ranges to be in [0, n] 
        vector<pair<int, int> > wateringIntervalsV;
        for (int i = 0 ; i != ranges.size(); ++i) {
            if (ranges[i] == 0) {
                continue; // Skip zero range taps
            }
            auto lo = max(0, i - ranges[i]);
            auto hi = min(n, i + ranges[i]);
            wateringIntervalsV.push_back({lo, hi});
        }
        
        // All of taps have zero range => watering impossible
        if (wateringIntervalsV.size() == 0) {
            return -1;
        }
        
        // Adopt the following greedy approach to water the entire garden
        // with the minimum number of taps:-
        // (1) From the taps yet to be processed, select the tap which waters the widest
        //     interval range possible (i.e extends the most from current time point)
        // (2) Eliminate the other taps whose watering range is wholly subsumed by
        //     the tap selected.
        // (3) We are trying to water max portion of garden with a single tap selected
        //     in (1) so this will lead to minimum number of taps required overall
        // (4) 
        // (A) If there are any taps whose watering range overlaps partially with tap
        //     selected in (1), select the particular one which extends the most beyond
        //     the end of watering range of currently selected tap. Go to step (2)
        // (B) If no partially overlapping taps get selected, if there are taps whose
        //     range commences at end of watering range of currently selected tap, go
        //     to step (1)
        // (C) If no taps satisfy the criterion in (4)(A) & (4)(B) above, there is a 
        //     gap in watering range => error

        // Sort the watering interval ranges in the ascending order of their start locations
        sort(wateringIntervalsV.begin(), wateringIntervalsV.end(),
             [&](const auto & i1, const auto & i2) {
                if (i1.first == i2.first) {
                    return i1.second > i2.second;
                }
                return i1.first < i2.first;
             });

        if (wateringIntervalsV[0].first > 0) {
            // First watering interval ordered as per start locations doesn't commence
            // at location 0 => impossible to water entire range [0, n]
            return -1;
        }
        
        // Iterate over the water range intervals in the ascending order of start locations
        int minTaps = 0;
        int wiIdx = 0;
        int currIntervalEnd = wateringIntervalsV[wiIdx].second;
        while (wiIdx != wateringIntervalsV.size()) {
            // Current watering interval is selected (requires a new tap)
            ++minTaps;
            
            currIntervalEnd = 
                max(currIntervalEnd, wateringIntervalsV[wiIdx].second);
            
            if (currIntervalEnd == n) {
                // Current watering interval endpoint hits end of watering range
                // => no new taps required
                return minTaps;
            }
            
            // Skip all taps with watering intervals ranges overlapping with current
            // selected interval, except the one which extends the most beyond the end
            // of the current interval; or commences just at the end.
            // Unskipped tap watering range is selected for next iteration
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

            // Advance to next tap/watering interval range
            wiIdx = j;
            currIntervalEnd = nextIntervalEnd;
        }
        return -1;
    }
};
