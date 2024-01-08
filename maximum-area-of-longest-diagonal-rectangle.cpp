// n => dimensions.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        long long longDiagSqrd = 0;
        long long maxArea = 0;
        // Iterate over each rectangle sequqntially
        for (auto & dim : dimensions) {
            // Compute current rectangle diagonal
            long long l = dim[0];
            long long w = dim[1];
            long long diagSqrd = (l * l) + (w * w);
            if (diagSqrd > longDiagSqrd) {
                // Current rectangle diagonal is the max seen so far
                // => update the max area
                longDiagSqrd = diagSqrd;
                maxArea = l * w;
            } else if (diagSqrd == longDiagSqrd) {
                // Current rectangle diagonal is identical to max seen so far
                // => update the max area to max val
                maxArea = max(maxArea, l * w);
            }
        }    
        return maxArea;
    }
};
