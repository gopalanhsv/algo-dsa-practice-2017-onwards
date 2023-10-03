// n => points.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)

const double PI = M_PI;

class Solution {
public:
    int
    visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        // Execute a circular ccw 360 degree scan round the fixed location with the specified
        // viewing angle determining the number of points visible in each of the possible scan
        // areas; tracking the maximum points visible within the scan area at any of the
        // angular locations
        
        // Circular scan translates to running a sliding window of viewing angle size
        // around all of the points (expressed in angular format) around the fixed 'location'
        
        // Convert each of points to polar co-ordinates relative to the 'location' i.e the fixed
        // 'location' is taken as the origin intead of (0, 0) and polar-cordinates are computed
        // relative to that. This is due to the fact that the ccw rotation happens around the fixed
        // 'location' for viewing the other points and the ccw rotation angle needs to computed
        // relative to the same.

        // For polar co-ordinates (r, theta), we are interested only in the angle and not the
        // distance 'r' as only the angle/field of view matters and not the distance
    
        // Array of point co-ords angles of each point relative to rotation centre location
        vector<double> pointAnglesV;
        // Number of points coincident with centre/point of rotation (these will always be viewable)
        int nPointsAtCenter = 0;
        computeAngleForPoint(points, location, pointAnglesV, nPointsAtCenter);

        // Sort the points in ascending order of their polar angles so that
        // sliding window can be applied over it
        sort(pointAnglesV.begin(), pointAnglesV.end());
        // Window size would be the viewing angle
        double viewAngleSz = angle;
        // Tracks max number of visible points in window/viewing angle
        auto nMaxPoints = 0;
        auto sWinStart = 0;
        auto nPoints = pointAnglesV.size();
        // Keeping adding new point to the window
        for (auto sWinEnd = 0; sWinEnd != nPoints; ++sWinEnd) {
            // Current point at 'sWinEnd' gets added to viewing window
            auto currPointAngle = pointAnglesV[sWinEnd];
            // Eliminate points which lie outside the viewing angle range by shrinking
            // window at the start
            while (currPointAngle - pointAnglesV[sWinStart] > viewAngleSz) {
                ++sWinStart;
            }
            // Number of visible points ending at 'pointAnglesV[sWinEnd]'
            auto nPoints = sWinEnd - sWinStart + 1;
            // Update the max number of visible points
            nMaxPoints = max(nPoints, nMaxPoints);
        }
        
        return nMaxPoints + nPointsAtCenter;
    }
    
private:
    
    void
    computeAngleForPoint(
        vector<vector<int>>& points, vector<int>& location, vector<double>& pointAnglesV, int & nPointsAtCenter) {

        // Co-ordinates of the fixed location/centre around which rotation occurs for viewing
        double centerX = location[0];
        double centerY = location[1];
        
        nPointsAtCenter = 0;
        // Iterate over each point
        for (auto & point : points) {
            double pointX = point[0];
            double pointY = point[1];
            if ((pointX == centerX) && (pointY == centerY)) {
                // Point is coincident with rotation center => always visible/viewable
                ++nPointsAtCenter;
            } else {
                // Compute the angle in degrees between the line joining current point to center and
                // the X - axis
                double pointAngle = atan2((pointY - centerY), (pointX - centerX)) * 180  / PI;
                // Normalize the angle to [0, 360] as 'atan2' gives in range [-PI, PI] i.e [-180, +180]
                if (pointAngle < 0) {
                    pointAngle += 360;
                }
                // The angle is added to the array. Need to also add 'angle + 360' to simulate circular
                // array as a circular scan gets done from end of array back to beginning
                pointAnglesV.emplace_back(pointAngle);
                pointAnglesV.emplace_back(pointAngle + 360);
            }
        }
    }
};
