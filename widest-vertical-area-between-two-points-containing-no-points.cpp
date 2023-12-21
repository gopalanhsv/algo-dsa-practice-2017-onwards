// n => points.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    int
    maxWidthOfVerticalArea(vector<vector<int>>& points) {
        // Base case of no/single point
        if (points.size() < 2) {
            return 0;
        }

        // Since height of the area forming rectangle is fixed (infinity as it extends
        // vertically), only the distance between x coords needs to be considered.
        // Problem reduces to finding the max width/distance between x-coords.
        // Sort points in non-decreasing order based on their x-coords and
        // determine the max X-axis distance between consecutive points
        struct PointXCoordCmpObj {
            bool
            operator()(const vector<int>& p1, const vector<int>& p2) {
                return p1[0] <= p2[0];
            }
        };
        sort(points.begin(), points.end(), PointXCoordCmpObj());
        
        // Iterate through the sorted x-coord points
        auto widestWidth = 0;
        //int prevX = points[0][0];
        auto n = points.size();
        for (auto i = 1; i != n; ++i) {
            widestWidth = max(widestWidth, points[i][0] - points[i - 1][0]);
        }
        
        return widestWidth;
    }
};
