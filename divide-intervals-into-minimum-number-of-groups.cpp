// n => intervals.size()
// Time Complexity : O(nlogn)
// Space Complexity : O(n)

class Solution {
public:
    int
    minGroups(vector<vector<int>>& intervals) {
        // Base case of no interval/single interval
        if (intervals.empty()) {
            return 0;
        }
        
        if (1 == intervals.size()) {
            return 1;
        }
        
        // Minimum number of groups required would be the
        // maximum number of overlapping intervals   
        
        // All we need to do is to maintain a counter.
        // Each time an interval starts we need to increment the counter
        // and each time an interval ends we need to decrement the counter.
        // Max value of the counter during the process will give the max number
        // of overlapping intervals and hence the minimum number of groups
        
        // For going through intervals in the appropriate time based
        // tick order; sort the start times and end times together; and have
        // some attribute to distinguish the two while going through them
        // (can use a +1 for start time and -1 for end time and use this as a
        // counter itself)
        vector<pair<int, int> > startEndTimeV;
        for (auto & i : intervals) {
            // Add start time with +1
            startEndTimeV.emplace_back(pair<int, int>({i[0], 1}));
            // Add end time with -1. Adding a + 1 to end time to account
            // for overlaps between end of an interval and beginning of a
            // new interval as same timestamp
            startEndTimeV.emplace_back(pair<int, int>({i[1] + 1, -1}));
        }
        
        // Sort the interval times
        sort(startEndTimeV.begin(), startEndTimeV.end());
        
        // Iterate through the combined sorted start/end times in sorted order
        // adding +1 for start time and -1 for end time
        int nOverlappingIntervals = 0;
        int minGroups = 0;
        for (auto & intervalTsInfo : startEndTimeV) {
            nOverlappingIntervals += intervalTsInfo.second;
            minGroups = max(minGroups, nOverlappingIntervals);
        }
        
        return minGroups;
    }
};
