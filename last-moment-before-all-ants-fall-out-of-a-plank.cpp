// n => left.size(), m => right.size()
// Time complexity : O(max(m, n))
// Space complexity : O(1)

class Solution {
public:
    int
    getLastMoment(int n, vector<int>& left, vector<int>& right) {
        
        // It is pretty clear that even after two ants collide and
        // change directions, we have swapped/name changed ants (which
        // collided and changed direction) at exactly locations as if
        // collision has not at all occurred. Collision is just taking
        // attention away from actual calculation -- it behaves more or
        // less as a non-event except for certain ants which just
        // change directions and get a longer time to walk the plank
        
        // Collision has no effect on the time of last ant to leave
        // the plank from either ends
        
        if (left.empty() && right.empty()) {
            return 0;
        }
        
        // Since time starts at 0, maximum time unit at which a left
        // moving ant would drop off the left end of the plank is
        // time taken for rightmost left moving ant to reach end of
        // plank (position 0)       
        int maxLeftPos = 0;
        for (auto & l : left) {
            maxLeftPos = max(l, maxLeftPos);
        }
        // Since time starts at 0, maximum time unit at which a right
        // moving ant would drop off the right end of the plank is
        // time taken for leftmost right moving ant to reach end of
        // plank (position n)  
        int minRightPos = n;
        for (auto & r : right) {
            minRightPos = min(r, minRightPos);
        }
        
        // So max time taken for all ants to leave plank would be the
        // maximum of time take for rightmost left moving ant to drop
        // off the plank left edge; or leftmost right moving ant to
        // drop off the plank right edge

        return max(maxLeftPos, n - minRightPos);
    }
};
