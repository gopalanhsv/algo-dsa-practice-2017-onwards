// n => arrays.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    maxDistance(vector<vector<int>>& arrays) {
        if (arrays.size() < 2) {
            // Max/min will end up from same array => not allowed
            return 0;
        }
        
        // Max distance would be the difference between the maximum and the
        // minimum number across the entire set of elements within the arrays
        // (with the elements max and min being from different arrays)
        
        // As each array is sorted in ascending order, 1st element is the max
        // and last element is the max value for that array
        // We just need to calculate the absolute
        // diff between the maximum and minimum value (with the values 
        // selected being from different arrays) and select the max diff 
        
        auto & array0 = arrays[0];
        // Tracks the minimum value seen so far across arrays
        auto minSeenSoFar = array0[0];
        // Tracks the maximum value seen so far across arrays
        auto maxSeenSoFar = array0[array0.size() - 1];
        // Tracks the maximum distance computed so far
        int maxDist = 0;
        // Iterate over all arrays from 2nd array onwards sequentially
        int nArrays = arrays.size();
        for (int arrId = 1; arrId != nArrays; ++arrId) {
            // Min and max val for the current array
            auto & array = arrays[arrId];
            auto & arrMax = array[array.size() - 1];
            auto & arrMin = array[0];
            
            // Max dist taking current array into account will be the absolute
            // diff between current array min and max seen so far (earlier arrays);
            // OR diff between current array max and min seen so far (earlier array)
            maxDist = max(maxDist, arrMax - minSeenSoFar);
            maxDist = max(maxDist, maxSeenSoFar - arrMin);
            
            // Update the min and max value seen to far
            // to account for current array min/max values
            minSeenSoFar = min(minSeenSoFar, arrMin);
            maxSeenSoFar = max(maxSeenSoFar, arrMax);
        }
        
        return maxDist;
    }
};
