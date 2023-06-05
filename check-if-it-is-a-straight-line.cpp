// Time complexity : O(coordinates.size()) / O(n)
// Space complexity : O(1)

class Solution {
public:
    bool
    checkStraightLine(vector<vector<int>>& coordinates) {
        if (coordinates.size() <= 2)  {
            // Number of coordinates is l.e. 2 => only a point or 1 straight line
            return true;
        }
        
        // Point 0 and point 1
        auto & pt0 = coordinates[0]; // (x0, y0)
        auto & pt1 = coordinates[1]; // (x1, y1)
        
        // Slope of libe between points (x0, y0) & (x1, y1)
        // = (y1 - y0) / (x1 - x0)
        // Line Slope Numerator (y1 - y0)
        int slopeNumerator = pt1[1] - pt0[1];
        // Line Slope Denominator (x1 - x0)
        int slopeDenominator = pt1[0] - pt0[0];
        
        // For all points to be on a straight line, all the lines formed by various
        // co-ordinates with point0 should have same slope as that of line between pt1 and pt0
        
        // That is, for a point i with coordinates (xi, yi)
        // (yi - y0) / (xi - x0) = slopeNumerator / slopeDenominator
        // or (slopeDenominator) * (yi - y0) = (slopeNumerator) * (xi - x0)
        // Iterate through all coordinates and test for equality of above expression
        for (int i = 2; i != coordinates.size(); ++i) {
            auto & pti = coordinates[i];
            if ((slopeDenominator * (pti[1] - pt0[1])) != 
                (slopeNumerator * (pti[0] - pt0[0]))) {
                return false;
            }
        }
        
        return true;
    }
};
