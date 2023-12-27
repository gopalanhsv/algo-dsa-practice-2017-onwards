// n => colors.size()/neededTime.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    minCost(string colors, vector<int>& neededTime) {
        // Objective is to have nil consecutive balloons on the rope with identical colors.
        // From a continuous streak of identical colored balloons; retain one balloon and remove
        // the rest. For the removal to be done in the shortest possible time, retain the balloon
        // requiring maximum removal time from amongst those having the identical colors
        
        // Track the total of removal times for each balloon; along with the max removal time
        // required for each consecutive series of identical colored balloons. Retain only the
        // balloon requiring maximum removal time from each streak of same colored balloons
        auto totalRemovalTime = neededTime[0];
        auto maxRemovalTime = neededTime[0];
        // Iterate over each balloon sequentially
        for (auto bId = 1; bId < colors.size(); ++bId) {
            
            totalRemovalTime += neededTime[bId];
            if (colors[bId] != colors[bId - 1]) {
                // Current ballon not identical in color to previous
                // Retain only the balloon requiring max removal time from the previous color
                // streak; dump the rest
                totalRemovalTime -= maxRemovalTime;
                // Reset params for new streak of balloons
                maxRemovalTime = 0;
            }
            // Update max removal time for current streak of identical colored balloons
            maxRemovalTime = max(maxRemovalTime, neededTime[bId]);
        }
        
        // Adjust for last streak of same colored balloons
        auto minTimeToMakeColorful = (totalRemovalTime - maxRemovalTime);
        return minTimeToMakeColorful;
    }
};
