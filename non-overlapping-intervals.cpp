// n => intervals.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    int
    eraseOverlapIntervals(vector<vector<int>>& intervals) {
        
        // Adopt the greedy method of only dropping intervals which
        // overlap with the maximum number of other mutually non-overlapping
        // intervals. This ensures that dropping such an interval (being the
        // longest and hence overlapping with maximum number of other mutually
        // non overlapping intervals) will result in removal of minimum
        // number of overlapping intervals
        
        // Sort the intervals in the ascending order of finish times.
        // Amongst those intervals having the same finish time, sort in
        // such a fashion s.t. intervals which are the longest come at the end
        struct IntervalCmpObj {
            bool
            operator()(const vector<int>& i1, const vector<int>& i2) {
                auto & s1 = i1[0];
                auto & e1 = i1[1];
                auto & s2 = i2[0];
                auto & e2 = i2[1];
                if (e1 == e2) {
                    // Finish times same, prioritise shorter intervals
                    return (e1 - s1 < e2 - s2);
                }
                return e1 < e2;
            }
        };
        
        sort(intervals.begin(), intervals.end(), IntervalCmpObj());
        
        // Iterate over the sorted intervals (in order of end times & shorter
        // duration first) sequentially
        int nOverlappingIntervalsToBeRemoved = 0;
        int prevIntervalEndTime = intervals[0][1];
        for (int i = 1; i != intervals.size(); ++i) {
            auto & currIntervalStartTime = intervals[i][0];
            auto & currIntervalEndTime = intervals[i][1];
            
            // Current interval is removed if it overlaps with
            // any previous interval
            if (currIntervalStartTime < prevIntervalEndTime) {
                // Remove current interval
                ++nOverlappingIntervalsToBeRemoved;
            } else {
                // Current interval not removed. Update previous interval
                // end time to that of current
                prevIntervalEndTime = currIntervalEndTime;
            }
        }
        
        return nOverlappingIntervalsToBeRemoved;
    }
};
