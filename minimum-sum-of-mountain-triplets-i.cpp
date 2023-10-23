// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(n)
class Solution {
public:
    int
    minimumSum(vector<int>& nums) {
        auto arrSz = nums.size();
        if (arrSz < 3) {
            // Base case of array not supporting any triplets
            return -1;
        }

        // Smallest possible triplet sum which includes a number at index 'j' as the
        // peak/mid of a mountain triplet will be the one which includes the minimum
        // element to left of index 'j' and minimum element to the right of
        // index 'j' which satisfy the triplet constraints

        // Precompute min element to right at each index
        vector<int> minElemToRightV(arrSz, numeric_limits<int>::max());
        for (int i = arrSz - 2; i > 0; --i) {
            minElemToRightV[i] = min(minElemToRightV[i + 1], nums[i + 1]);
        }
        
        auto minElemToLeft = nums[0];
        int minTripletSum = numeric_limits<int>::max();
        // Iterate over potential candidate peaks/mid elements of possible triplets
        for (auto j = 1; j < arrSz - 1; ++j) {
            auto & currElem = nums[j];
            if ((currElem > minElemToLeft) && (currElem > minElemToRightV[j])) {
                // Current element at 'j' forms a mountain triplet with the smallest 
                // element to both its left and right
                // Compute min triplet sum formed with current element as mid/peak element
                auto tripletSum = minElemToLeft + currElem + minElemToRightV[j];
                // Update minimum triplet sum
                minTripletSum = min(minTripletSum, tripletSum);
            }
            
            minElemToLeft = min(minElemToLeft, currElem);
        }
        
        return (minTripletSum == numeric_limits<int>::max()) ? -1 : minTripletSum;
    }
};
