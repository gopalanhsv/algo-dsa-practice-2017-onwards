// n => intervals.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)
class Solution {
public:
    int
    removeCoveredIntervals(vector<vector<int>>& intervals) {

        // Sort intervals in ascending order of start times; for intervals with identical
        // start times, longer duration intervals are preferred first as they may
        // cover subsequent intervals
        sort(intervals.begin(), intervals.end(),
            [&](const auto & i1, const auto & i2) {
                if (i1[0] == i2[0]) {
                    return i1[1] > i2[1];
                }
                return i1[0] < i2[0];
            });
        
        // Init first interval as covering interval
        auto nRemainingIntervals = 1;
        auto coveringIntervalLeft = intervals[0][0];
        auto coveringIntervalRight = intervals[0][1];
        // Iterate over the sorted intervals sequentially
        for (auto & interval : intervals) {
            // Current interval [l, r)
            auto l = interval[0];
            auto r = interval[1];
            if ((l >= coveringIntervalLeft) && (r <= coveringIntervalRight)) {
                // Current interval [l, r) is covered and hence skipped
                continue;
            }
            
            // Current interval is not covered by exiting covering interval => it
            // becomes the new covering interval and is retained
            coveringIntervalLeft = l;
            coveringIntervalRight = r;
            ++nRemainingIntervals;
        }
        
        return nRemainingIntervals;
    }
};
