class Solution {
public:
    int
    shipWithinDays(vector<int>& weights, int D) {
        // Minimum ship capacity should allow for shipping of package with max
        // weight in one day, as packages cannot be split for shipping across days
        // Maximum ship capacity would be the sum of all package weights,
        // (for single day shipping)
        int minShipCapacity = 0;
        int maxShipCapacity = 0;
        for (auto & wt : weights) {
            minShipCapacity = max(minShipCapacity, wt);
            maxShipCapacity += wt;
        }
        
        // Find a minimum shipping capacity in range [minShipCapacity, maxShipCapacity]
        // with which packages can be shipped in 'D' days via binary search
        // Do this via pincer movement of compressing the search range till it
        // reduces to one element
        int l = minShipCapacity;
        int r = maxShipCapacity;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (capacitySufficientToShipPackages(mid, weights, D)) {
                // 'mid' will now be the upper bound of search range
                r = mid;
            } else {
                // Capacity of 'mid' is insufficient, search in upper
                // half of range above 'mid'
                l = mid + 1;
            }
        }
        
        return l;
    }
    
private:
    
    bool
    capacitySufficientToShipPackages(int capacity, vector<int>& weights, int maxDays) {
        int nDays = 0;
        int sumOfAllPkgWtsForTheDay = 0;
        // Iterate over the package weights in order of loading to determine the
        // min number of reqd days for shipping (with given ship capacity)
        for (auto & weight : weights) {
            // Add current package to set of packages to be shipped for
            // day and check if it can be accomodated in the ship. If no
            // accomodation possible, ship the package next day
            sumOfAllPkgWtsForTheDay += weight;
            if (sumOfAllPkgWtsForTheDay > capacity) {
                ++nDays;
                sumOfAllPkgWtsForTheDay = weight; 
            } else if (sumOfAllPkgWtsForTheDay == capacity) {
                ++nDays;
                sumOfAllPkgWtsForTheDay = 0;
            }
        }
        
        nDays += (sumOfAllPkgWtsForTheDay == 0) ? 0 : 1;
        
        return nDays <= maxDays;
    }
};
