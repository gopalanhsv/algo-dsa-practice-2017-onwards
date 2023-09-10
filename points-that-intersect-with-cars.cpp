// n => nums.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    int
    numberOfPoints(vector<vector<int>>& nums) {
        if (nums.empty()) {
            return 0;
        }
        
        // Sort the array in the ascending order of car start co-ords
        sort(nums.begin(), nums.end(),
            [&](const auto & p1, const auto & p2) {
                if (p1[0] == p2[0]) {
                    return p1[1] > p2[1];
                }
                return p1[0] < p2[0]; 
            });
        
        // Tracks num unique points covered by car (partially or wholly)
        int nPoints = 0;
        // Initialize interval start/end to first cars' coords
        int runningIntervalStart = nums[0][0];
        int runningIntervalEnd = nums[0][1];
        // Iterate over each of the car intervals in sequence eleiminating overlaps
        for (auto i = 1; i != nums.size(); ++i) {
            auto & coord = nums[i];
            auto & start = coord[0];
            auto & end = coord[1];
            if (start > runningIntervalEnd) {
                // Current car interval doesn't overlap with the previously running
                // interval => end the running interval, count its points contrib
                // and start a new running interval here
                nPoints += runningIntervalEnd - runningIntervalStart + 1;
                runningIntervalStart = start;
            }
            // Update the end of current running interval
            runningIntervalEnd = max(runningIntervalEnd, end);
        }
        // Add the points contrib due to last running interval
        nPoints += runningIntervalEnd - runningIntervalStart + 1;
        
        return nPoints;
    }
};
