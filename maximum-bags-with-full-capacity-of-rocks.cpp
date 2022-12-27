class Solution {
public:
    int
    maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
        int nBags = rocks.size();
        
        // Tracks the number of bags
        int nFullBags = 0;
        // Tracks the available spare capacity per bag (only for bags with space)
        vector<int> avlSpareCapV;
        // Determine the number of fully topped bags and free available
        // spare for the remaining bags
        for (int i = 0; i != nBags; ++i) {
            auto spareCapacity = capacity[i] - rocks[i];
            if (spareCapacity > 0) {
                avlSpareCapV.emplace_back(spareCapacity);
            } else {
                ++nFullBags;
            }
        }
        
        // Adopt the greedy approach of always choosing the bag with least
        // spare capacity available at each step to fill to max possible capacity
        // with rocks from the additional available rocks. This strategy ensures
        // that max possible bags will be filled up to their capacity
        
        // Sort the bags in non-decreasing order of their spare capacity
        sort(avlSpareCapV.begin(), avlSpareCapV.end());
        // Iterate over the spare capacity in ascending order
        for (auto & bagSpareCap : avlSpareCapV) {
            if (additionalRocks < bagSpareCap) {
                // Additional rocs insufficient to fill spare
                // capacity in current and subsequent bags
                break;
            }
            // Top up the current bag
            additionalRocks -= bagSpareCap;
            ++nFullBags;
        }
        
        return nFullBags;
    }
};
