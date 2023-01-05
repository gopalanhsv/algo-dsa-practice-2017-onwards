class Solution {
public:
    int
    findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() < 2) {
            // base case of 0/1 balloon
            return points.size();
        }
        // For finding the minimum number of arrows to shoot
        // down all ballons, we need to find that total number
        // of balloon coordinate overlap sets. If an arrow is
        // shot vertically within any overlap region/set, it will
        // burst all ballons in that overlap region/set.
        
        // A ballon extends from [xstart, xend] closed range interval
        // All the other ballons whose diameter falls in that range
        // overlap with that ballon
        
        // Take the greedy approach that given a ballon, find all the
        // other ballons which overlap with it, shoot down all the
        // ballons with a single arrow in overlap region; then go to
        // next ballon and repeat process. We are optimizing the local
        // problem at each step.
        
        // Sort all balloons in the ascending order of their start coordinates
        struct BalloonIntervalStartCmpObj {
            bool
            operator()(const vector<int>& p1, const vector<int>& p2) {
                if (p1[0] == p2[0]) {
                    // When xstart same, prefer those will lower xend 
                    return p1[1] < p2[1];
                }
                return p1[0] < p2[0];
            }
        };
        sort(points.begin(), points.end(), BalloonIntervalStartCmpObj());
        
        // Overlap region amongst a set of balloons i = 1 to x
        // overlap start = max of xstart of all balloons overlapping
        // overlap end = min of xend of all balloons overlapping
        // An arrow between overlap start and end will blast all balloons in overlap
        
        // Iterate over all balloons in the ascending order of their start coordinates
        // Find all the subsequent balloons which overlap with it and shoot them down with
        // a single arrow
        int nArrows = 1;
        int currBalloonEnd = points[0][1];
        for (int bId = 1; bId != points.size(); ++bId) {
            // New balloon
            auto & nb = points[bId];
            int newBalloonStart = nb[0];
            if (newBalloonStart > currBalloonEnd) {
                // New balloon no longer overlaps with any of previous
                // balloons, so new balloon overlap region has commenced
                // and requires a new arrow to shoot it down
                ++nArrows;
                // Update current ballon end overlap location to that of this new balloon
                currBalloonEnd = nb[1];
            } else {
                // New balloon overlaps with current balloon. Update current
                // balloon overlap end location to minimum of new balloon end location
                // current balloon end location.
                // THIS STEP IS VERY IMPORTANT
                currBalloonEnd = min(currBalloonEnd, nb[1]);
            }
        }
        return nArrows;
    }
};
