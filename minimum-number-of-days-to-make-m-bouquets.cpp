// n => bloomDay.size(), M => max_element(bloomDay)
// Time complexity : O(nlogM)
// Space complexity : O(1)

class Solution {
public:
    int
    minDays(vector<int>& bloomDay, int m, int k) {
        if (bloomDay.size() < (long long)m * k) {
            // Base case : Number of flowers is less than number
            // required for 'm' bouquets
            return -1;
        }
        
        // Min number of days possible for all flowers to bloom and usable
        // in bouquets would be 1 (from input spec)
        int minimumDays = 1;
        // Max number of days possible for all flowers to bloom and usable
        // in bouquets would be max value in 'bloomDay' vector
        int maximumDays = 1;
        for (auto & bd : bloomDay) {
            maximumDays = max(bd, maximumDays);
        }
        
        // Execute a binary search in the range [minimumDays, maximumDays]
        // to find the minimum number of days 'x' s.t sufficient adjacent flowers
        // bloom in 'x' days and can be used to make 'm' bouquets
        int l = minimumDays, r = maximumDays;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (possibleToMakeBouquets(bloomDay, m, k, mid)) {
                // Possible to make 'm' bouquets from 'k' adjacent blooms in 'mid'
                // days. This fixes upper bound of search range. Check for
                // bouquet making possiblilty with lower number of days
                r = mid;
            } else {
                // Impossible to make 'm' bouquets from 'k' adjacent blooms in 'mid'
                // days. Check for bouquet making possiblilty with higher number of days
                l = mid + 1;
            }
        }
        
        // Search terminates with l and r converging to each other in a pincer movement with
        // r being the minimum number of days at which required bouquets are available
        return l;
    }
    
private:
    
    bool
    possibleToMakeBouquets(vector<int>& bloomDay,
                           int nBouquets, int nBloomsPerBouquet, int nDays) {
        // Determine the number of bouquets which can be made using 
        // 'nBloomsPerBouquet' adjacent blooms in 'nDays'
        int adjBloomCnt = 0;
        int nPossibleBouquets = 0;
        for (auto & bd : bloomDay) {
            if (nDays >= bd) {
                // Current flower has bloomed
                // Increment count of adjacent blooms
                if (++adjBloomCnt == nBloomsPerBouquet) {
                    // Count of adjacent blooms suffices for a bouquet
                    ++nPossibleBouquets;
                    // Commence a new bouquet from next bloom onwards
                    adjBloomCnt = 0;
                }
            } else {
                // Current flower not bloomed
                // Reset the count of adjacent blooms
                adjBloomCnt = 0;
            }
        }
        
        return nPossibleBouquets >= nBouquets;
    }
};
