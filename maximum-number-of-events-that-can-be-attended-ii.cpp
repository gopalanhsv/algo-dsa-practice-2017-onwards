// n => events.size()
// Time complexity : O(nlogn) + O(nklogn)
// Space complexity : O(nk)
class Solution {
public:
    
    int
    maxValue(vector<vector<int>>& events, int k) {       
        // Sort the events in the ascending order of respective 'start time'
        // This allows to quickly search for the closest next event which
        // does not overlap with the current event via binary search
        
        // With each event, one has the option of either attending or
        // not attending that event => use of DFS combined with DP
        // for fast lookup
        
        // Initialize
        init(events, k);
        
        // Compute the max sum of values possible under the given
        // constraints by trying out all options via DFS
        return maxValueViaTopDownMemoization(events, k);
    }
    
private:
    
    void
    init(vector<vector<int>>& events, int k) {
        _nEvents = events.size();

        // Sort the events in the ascending order of respective 'start time'
        sort(events.begin(), events.end(),
             [&](auto & e1, auto & e2) {
                return e1[0] < e2[0]; 
             });
    }

    int
    closestNextCandidateEvent(int currIdx, vector<vector<int>>& eventsV) {
        int lo = currIdx + 1;
        int hi = eventsV.size() - 1;
        int minReqdStartDay = eventsV[currIdx][1] + 1;
        if (lo > hi) {
            return -1;
        }
        if (eventsV[hi][0] < minReqdStartDay) {
            return -1;
        }
        if (eventsV[lo][0] >= minReqdStartDay) {
            return lo;
        }

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (eventsV[mid][0] >= minReqdStartDay) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
  
        return lo;
    }
    
    int
    maxValueViaTopDownMemoizationDFS(
        vector<vector<int>>& events, int nAllowedEvents, int currEventIdx) {
        
        if ((currEventIdx >= _nEvents) || (0 == nAllowedEvents)) {
            return 0;
        }

        if (-1 != _memoTbl[currEventIdx][nAllowedEvents]) {
            return  _memoTbl[currEventIdx][nAllowedEvents];
        }

        int maxValWithoutCurrEvent = 
            maxValueViaTopDownMemoizationDFS(events, nAllowedEvents, currEventIdx + 1);

        auto & ce = events[currEventIdx];
        auto & ceVal = ce[2];
        int maxValWithCurrEvent = ceVal;
        int nextCandidateEventIdx =
            closestNextCandidateEvent(currEventIdx, events);
        if (-1 != nextCandidateEventIdx) {
            maxValWithCurrEvent +=
                maxValueViaTopDownMemoizationDFS(
                    events, nAllowedEvents - 1, nextCandidateEventIdx);     
        }

        _memoTbl[currEventIdx][nAllowedEvents] =
            max(maxValWithoutCurrEvent, maxValWithCurrEvent);
        
        return _memoTbl[currEventIdx][nAllowedEvents];
    }
    
    int
    maxValueViaTopDownMemoization(vector<vector<int>>& events, int k) {
        _memoTbl.resize(_nEvents, vector<int>(k + 1, -1));
        
        return maxValueViaTopDownMemoizationDFS(events, k, 0);
    }

    // Data members
    // Number of events
    int _nEvents;
    // Memoization DP table
    // _memoTbl[e][x] is the max value achievable by attending a combination of events
    // upto a maximum of 'x' events from the range of events [e, _nEvents - 1] i.e. 
    // from 'e' onwards inclusive (with the events sorted on the basis of their start times)
    vector<vector<int> > _memoTbl;
};
