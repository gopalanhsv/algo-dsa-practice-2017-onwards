// d => dist, n => team.size()
// Time complexity : O(n)
// Space complexity : O(d)

class Solution {
public:
    int
    catchMaximumAmountofPeople(vector<int>& team, int dist) {
        // Adopt greedy approach of using current 'it' team to catch farthest possible
        // unassigned 'non-it' team seen previously withing allowed distance 'dist'
        // Adopt greedy approach of using current 'non-it' team to be caught by farthest
        // possible unassigned 'it' team seen previously within allowed distance 'dist'
        // Unassigned => an it/non-it team which 'has not yet caught/has yet to be caught" by
        // a non-it/it team respectively
        auto n = team.size();
        int nearestNonItIdx = -1;
        int nearestItIdx = -1;
        // 2 queues to track valid non-it which are yet to be caught by an it team;
        // and it team which is yet to catch a non-it team
        // Farthest teams are at Q front
        queue<int> nonItIdxQ;
        queue<int> itIdxQ;
        int nCaught = 0;
        // Iterate over the teams from L->R
        for (auto i = 0; i != n; ++i) {
            
            // Remove it team which is beyond range i.e cannot catch a non-it
            // team from index 'i' onwards
            if (!itIdxQ.empty() && (i - itIdxQ.front() > dist)) {
                itIdxQ.pop();
            }
            // Remove non-it team which is beyond range i.e cannot be caught by
            // an it team from index 'i' onwards
            if (!nonItIdxQ.empty() && (i - nonItIdxQ.front() > dist)) {
                nonItIdxQ.pop();
            }
            
            if (team[i] == 0) {
                // Current team is nonIT team
                if (!itIdxQ.empty()) {
                    // Current non-it team is assigned to be caught by
                    // the farthest possible it team seen so far
                    ++nCaught;
                    itIdxQ.pop();
                } else {
                    // Current non-it team is added to Q
                    nonItIdxQ.push(i);
                }
            }
            
            if (team[i] == 1) {
                // Current team is IT team
                if (!nonItIdxQ.empty()) {
                    // Current it team is assigned to be caught by
                    // the farthest possible non-it team seen so far
                    ++nCaught;
                    nonItIdxQ.pop();
                } else {
                    // Current it team is added to Q
                    itIdxQ.push(i);
                }
            }
        }
        
        return nCaught;
    }
};
