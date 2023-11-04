// n => nums.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {
public:
    int
    sumDistance(vector<int>& nums, string s, int d) {
        // Collision of robots can be treated as the two robots just exchanging
        // or swapping their bodies and continuing onwards => a robot continuing
        // on as if nothing has occurred.
        
        // Since collision is treated as a non-event, determine the final
        // positions of all robots
        auto nRobots = nums.size();
        // Copy of the robot positions (for avoiding overflows)
        vector<long long> posV(nums.begin(), nums.end());
        for (auto i = 0; i != nRobots; ++i) {
            auto & pos = posV[i];
            if (s[i] == 'L') {
                // Left moving robot => net movement of -d units
                pos -= d;
            } else {
                // Right moving robot => net movement of +d units
                pos += d;
            }
        }
        
        // Compute the distances between each pair of robots in
        // a smart fashion by sorting and using prefix sum for performace
        // Sort the robots in ascending order of their locations
        sort(posV.begin(), posV.end());

        const int moduloFactor = 1000000000 + 7;
        // Sum of distances between all robot pairs
        long long sumOfDistances = 0;
        long long prefixSumOfPriorLocations = 0;
        // Iterate over the robot locations in ascending order
        for (auto i = 0; i != nRobots; ++i) {
            long long pos = posV[i];
            // For robot located at current index 'i' (0-index), contribution to
            // sum of distances for all pairs of robots in the range [0, i - 1]
            // is (pos - posV[0]) + (pos - posV[1]) + (pos - posV[2]) + ....
            // ................. + (pos - posV[i - 2]) + (pos - posV[i - 1])
            // = {i * pos} - {posV[0] + posV[1] + posV[2] + .... + posV[i - 1] + posV[i]}
            // = {i * pos} - prefix sum of prior locations
            
            sumOfDistances += ((pos * i) - prefixSumOfPriorLocations);
            sumOfDistances %= moduloFactor;
            prefixSumOfPriorLocations += pos;
        }
        
        return sumOfDistances;
    }
};
