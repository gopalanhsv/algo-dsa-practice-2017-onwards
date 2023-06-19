// Time complexity : O(gain.size()) / O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    largestAltitude(vector<int>& gain) {
        // gain[i] = altitude[i + 1] - altitude[i]
        // => altitude[i + 1] = gain[i] + altitude[i]
        // altitude[0] = 0 (biker starts at altitude 0)
        // Iterate sequentially over the road trip points, computing the
        // altitude at each point while tracking the max altitude seen so far
        int maxAltitude = 0;
        int currAltitude = 0;
        for (auto gainAtCurrentPt : gain) {
            currAltitude += gainAtCurrentPt;
            maxAltitude = max(maxAltitude, currAltitude);
        }
        return maxAltitude;
    }
};
