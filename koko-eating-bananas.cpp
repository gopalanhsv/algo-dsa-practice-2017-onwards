// Time Complexity : O(NlogM), N : num piles, M : Max pile size
// Space Complexity : O(1)

class Solution {
public:
    int
    minEatingSpeed(vector<int>& piles, int h) {
        // At max eating speed, Koko would finish the pile with maximum bananas
        // (she can finish max 1 pile per hour)
        int maxSpeed = 0;
        for (auto & pile : piles) {
            maxSpeed = max(pile, maxSpeed);
        }
        
        // Minimum possible eating speed would be 1, as Koko prefers to eat
        // slowly and has an integer eating speed
        int minSpeed = 1;
        
        // Execute binary search in the closed range [minSpeed, maxSpeed] to
        // find the minimum speed at which Koko can finish eating all bananas
        // in 'h' hours
        int l = minSpeed, r = maxSpeed;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (canFinishEatingAllBananas(piles, h, mid)) {
                // Speed 'mid' becomes the higher bound on possible
                // speed at which Koko can finish all bananas in given time
                // Check if it is possible to eat at lower speeds and finish too
                // i.e search in lower part of range
                r = mid;
            } else {
                // Not possible for Koko to finish all bananas in given time at
                // speed 'mid'. She needs to eat faster. Search in upper part
                // of range at higher speeds
                l = mid + 1;
            }
        }
        
        // At end of search l & r converge in pincer movement to the
        // lowest possible speed at which Koko can finish all bananas
        return l;
    }
    
private:
    
    inline bool
    canFinishEatingAllBananas(vector<int>& piles, int h, int eatingSpeed) {
        // Compute the number of hours required to finish all piles
        // at given speed
        int numHrs = 0;
        for (auto & pile : piles) {
            // Max of one pile per hour (so not adding multiple piles together here)
            //numHrs += ceil((double)pile / eatingSpeed);
            numHrs += (pile - 1) / eatingSpeed + 1;
        }
        
        return numHrs <= h;
    }
};
