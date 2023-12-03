// n => mountain.size();
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    findPeaks(vector<int>& mountain) {
        vector<int> peaksV;
        // Iterate over the mountains from L->R
        auto nMountains = mountain.size();
        for (auto m = 1; m < nMountains - 1; ++m) {
            auto & prevMountain = mountain[m - 1];
            auto & currMountain = mountain[m];
            auto & nextMountain = mountain[m + 1];
            if ((currMountain > prevMountain) && (currMountain > nextMountain)) {
                // Current mountain is a peak
                peaksV.emplace_back(m);
                // Skip next mountain as 2 adjacent mountains can never be peaks
                ++m;
            }
        }
        return peaksV;
    }
};
