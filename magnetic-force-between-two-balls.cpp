// n => position.size(), M = max_element(position)
// Time complexity : O(nlogM + nlogn) 
// Space complexity : O(logn)

class Solution {
public:
    int
    maxDistance(vector<int>& position, int m) {
        // Sort the basket positions in ascending order
        sort(position.begin(), position.end());
        
        // Maximum value of magnetic force is between balls placed
        // in baskets at extreme/end positions
        int maxForce = position[position.size() - 1] - position[0];
        // Minimum value of magnetic force is between balls placed
        // in closest baskets
        int minForce = 1 ; //position[1] - position[0];
        //for (int i = 2; i < position.size(); ++i) {
        //    minForce = min(minForce, position[i] - position[i - 1]);
        //}
        
        // Execute a binary search for the maximum magnetic force in the range
        // [minForce, maxForce] which allows 'm' balls to be distributed in the given
        // baskets. That is, do a binary search for the maximum allowable distance 'x'
        // in the range [minForce, maxForce], enabling placement of all 'm' balls
        // in baskets with the minimum distance (minimum magentic force) between each
        // ball being 'x'
        int l = minForce, r = maxForce;
        while (l < r) {
            // l + 1 stunt for convergence. Reqd for l = mid setting
            int mid = l + 1 + (r - l) / 2;
            if (possibleToPlaceAllBallsInBaskets(position, mid, m)) {
                // Possible to distribute 'm' balls in baskets with
                // a distance of 'mid' in between
                // Set the lower bound for search range
                l = mid;
            } else {
                // Not possible to distribute 'm' balls in baskets with
                // a distance of 'mid' in between
                // Try with reduced space between the balls
                r = mid - 1;
            }
        }
        
        // Binary search terminates with l == r at end and l is the max distance
        // at which for which it is possible to distribute all balls in baskets
        return l;
    }
    
private:
    bool
    possibleToPlaceAllBallsInBaskets(vector<int>& position, int minDistanceBetweenBaskets,
                                     int numBalls) {
        
        // Determine how many balls can be placed in baskets with a 
        // minimum distance as specified
        int ballCnt = 1;
        int prevPos = position[0];
        for (int i = 1; i != position.size(); ++i) {
            if (position[i] - prevPos >= minDistanceBetweenBaskets) {
                ++ballCnt;
                prevPos = position[i];
            }
        }
        
        return ballCnt >= numBalls;
    }
};
