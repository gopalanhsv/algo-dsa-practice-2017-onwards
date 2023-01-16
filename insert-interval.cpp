class Solution {
public:
    vector<vector<int>>
    insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        
        vector<vector<int> > outIntervalsV;
        
        int newStart = newInterval[0];
        int newEnd = newInterval[1];
        
        int nIntervals = intervals.size();
        int i = 0;
        // Store all intervals ending prior to the new interval start time
        while (i < nIntervals && intervals[i][1] < newStart) {
            outIntervalsV.emplace_back(intervals[i]);
            ++i;
        }
        
        // Now merge all overlapping intervals which overlap with
        // new interval start time and extend through its duration till 
        // an interval is hit which commences after the new interval
        // end time.
        // Compute start of the merged interval
        int mergedIntervalStart = newStart;
        if (i < nIntervals) {
            mergedIntervalStart = min(mergedIntervalStart, intervals[i][0]);
        }
        // Compute end of the merged interval
        int mergedIntervalEnd = newEnd;
        while (i < nIntervals && intervals[i][0] <= newEnd) {
            mergedIntervalEnd = max(mergedIntervalEnd, intervals[i][1]);
            ++i;
        }
        // Add the merged interval to output
        outIntervalsV.emplace_back(
            vector<int>({mergedIntervalStart, mergedIntervalEnd}));
        
        // Store all intervals which commence after new interval end time
        while (i < nIntervals) {
            outIntervalsV.emplace_back(intervals[i]);
            ++i;
        }
        
        return outIntervalsV;
    }
};
