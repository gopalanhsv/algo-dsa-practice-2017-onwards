class Solution {
public:
    int
    countCollisions(string directions) {

        // Of the set of cars in the range [0, n - 1], all cars in the
        // closed range [0, lo] which are moving to 'left' do not experience
        // any collision, wherein 'lo + 1' is beyond the number of cars; or
        // car [lo + 1] is first car from the left of the range which is 
        // either stationary or moving to 'right'
        
        // Similarly, of the set of cars in the range [0, n - 1], all cars in the
        // closed range [hi, n - 1] which are moving to 'right' do not experience
        // any collision, wherein 'hi - 1' is beyond the number of cars; or
        // car [hi - 1] is first car from the right of the range which is 
        // either stationary or moving to 'left'
        
        // Of the remaining cars in the closed range [lo + 1, hi - 1]
        // 1. car moving to 'left' will collide with a 'stationary' car
        //    and become stationary (1 collision per left car)
        // 2. car moving to 'left' will collide with a 'right' car and become
        //    stationary (1 collision per each such left car and right car)
        // 3. car moving to 'right' will collide with a 'stationary' car
        //    and become stationary (1 collision per right car)
        // From the above it is clear each of the cars moving either to 'left'
        // or 'right' in the closed range [lo + 1, hi - 1] experience 1
        // collision each
        
        int nCars = directions.size();
        int lo = 0;
        // Skip cars (moving to left) to left of range which dont collide
        while ((lo < nCars) && (directions[lo] == 'L')) {
            ++lo;
        }
        int hi = nCars - 1;
        // Skip cars (moving to right) to right of range which dont collide
        while ((hi >= 0) && (directions[hi] == 'R')) {
            --hi;
        }
        
        if (lo >= hi) {
            // No collisions
            return 0;
        }
        
        // Count the number of cars moving either to 'left' or 'right' in
        // range [lo, hi]
        int nLeftRightCars = 0;
        while (lo <= hi) {
            if ((directions[lo] == 'L') || (directions[lo] == 'R')) {
                ++nLeftRightCars;
            }
            ++lo;
        }
        
        return nLeftRightCars;
    }
};
