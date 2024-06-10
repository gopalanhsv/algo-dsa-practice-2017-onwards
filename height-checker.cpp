// n => heightsV.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {
public:
    int
    heightChecker(vector<int>& heightsV) {
        if (heightsV.size() <= 1) {
            // No/single student
            return 0;
        }
        
        // Sort copy of heights vector
        vector<int> sortedHeightsV(heightsV.begin(), heightsV.end());
        sort(sortedHeightsV.begin(), sortedHeightsV.end());
        
        int nMoves = 0;
        // Compare the unsorted and sorted heights of students to determine
        // the number of student moves required to arrange all students
        // in order of non-decreasing heights
        for (auto i = 0; i != heightsV.size(); ++i) {
            if (heightsV[i] != sortedHeightsV[i]) {
                // Mismatch in sorted and unsorted heights
                ++nMoves;
            }
        }
        
        return nMoves;
    }
};
