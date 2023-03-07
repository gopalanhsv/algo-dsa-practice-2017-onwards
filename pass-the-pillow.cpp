class Solution {
public:
    int
    passThePillow(int n, int time) {
        // Time for pillow to reach last person in line from 1st person
        // would be 'n - 1' seconds
        // Time for pillow to reach 1st person in line from last person
        // would be 'n - 1' seconds
        const int travelTimeBetnLineExtremities = n - 1;
        // So time taken for circular round trip commencing from 1st
        // person and back would be 2(n - 1) seconds
        // Adjust time to account for all circular round trips from 1st person
        time = time % (2 * travelTimeBetnLineExtremities);
        
        // Pillow is back with 1st person post all circular trips
        if (time <= travelTimeBetnLineExtremities) {
            // Remaining time is l.e required for a trip from 1 to 'n'
            return 1 + time;
        }
        
        // Remaining time is g.t required for a trip from 1 to 'n'
        // Adjust time for pillow to reach 'n'
        time -= travelTimeBetnLineExtremities;
        // Remaining time is used up on the reverse trip from 'n' to 1
        return n - time;
    }
};
