class Solution {
public:
    long long
    findTheArrayConcVal(vector<int>& nums) {
        long long concatVal = 0;
        // Two pointers at array ends to track the numbers which
        // should be concatenated and then removed in each iteration
        int beginP = 0;
        int endP = nums.size() - 1;
        
        while (beginP < endP) {
            
            // Concat the values at array ends
            long long currConcatVal = nums[beginP];
            string hiNumStr = to_string(nums[endP]);
            for (auto & digit : hiNumStr) {
                currConcatVal = (10 * currConcatVal) + int(digit - '0');
            }
            // Add the concatenated value of numbers at begin and
            // and end of array to the total concatenated value
            concatVal += currConcatVal;
            // Remove element at begin and end of array. Shrink array
            ++beginP, --endP;
        }
        
        if (beginP == endP) {
            // Last array element yet to be removed and concatenated 
            concatVal += nums[beginP];
        }
        
        return concatVal;
    }
};
