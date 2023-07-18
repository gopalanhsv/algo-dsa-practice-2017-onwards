// Time complexity : O(arr.size()) / O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    sumOfSquares(vector<int>& nums) {
        int arrSz = nums.size();
        int splElemSqSum = 0;
        // Iterate over the array elements sequentially
        for (int i = 1; i <= arrSz; ++i) {
            auto & currElem = nums[i - 1];
            if (0 == arrSz % i) {
                // Current element is special
                // Add its square to the sum
                splElemSqSum += (currElem * currElem);
            }
        }
        
        return splElemSqSum;
    }
};
