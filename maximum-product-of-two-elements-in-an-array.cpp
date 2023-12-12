// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    maxProduct(vector<int>& nums) {
        auto arrSz = nums.size();
        if (arrSz < 2) {
            // Base case of array having less than 2 elements
            return 0;
        }
        
        // Maximum product of 2 array elements is formed by the
        // first maximum and the second maximum array elements
        
        // Iterate over the elements sequentially from L->R and determine
        // the value of 1st/2nd max elements
        auto firstMaximum = -1;
        auto secondMaximum = -1;
        for (int i = 0; i != arrSz; ++i) {
            auto & elem = nums[i];
            if (elem > firstMaximum) {
                secondMaximum = firstMaximum;
                firstMaximum = elem;
            } else if (elem > secondMaximum) {
                secondMaximum = elem;
            }
        }
        
        return ((firstMaximum - 1) * (secondMaximum - 1));
    }
};
