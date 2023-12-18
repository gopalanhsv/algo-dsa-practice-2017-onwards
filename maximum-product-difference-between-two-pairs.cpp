// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    maxProductDifference(vector<int>& nums) {
        
        // Maximum product difference is obtained between the maximum product the minimum
        // product. Since all array elements are +ve; maximum product is formed by the maximum
        // 2 elements and minimum product is formed by the minimum 2 elements
        
        // Iterate over the array and determine the 2 array maximums and 2 array minimums
        int firstMax = 0;
        int secondMax = 0;
        int firstMin = numeric_limits<int>::max();
        int secondMin = numeric_limits<int>::max();
        
        for (auto num : nums) {

            if (num >= firstMax) {
                secondMax = firstMax;
                firstMax = num;
            } else if (num > secondMax) {
                secondMax = num;
            }
            
            if (num <= firstMin) {
                secondMin = firstMin;
                firstMin = num;
            } else if (num < secondMin) {
                secondMin = num;
            }
        }
        
        // Difference of the product of 2 array max and 2 array mins
        return (firstMax * secondMax) - (firstMin * secondMin);
    }
};
