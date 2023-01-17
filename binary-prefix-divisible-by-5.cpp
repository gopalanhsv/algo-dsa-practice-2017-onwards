class Solution {
public:
    vector<bool>
    prefixesDivBy5(vector<int>& nums) {
        vector<bool> outV;
        // Iterate through the binary array from L->R sequentally
        int prefixDecNum = 0;
        for (auto num : nums) {
            // Construct decimal equivalent for the binary prefix
            // seen so far(from index 0 to current index)
            prefixDecNum <<= 1;
            prefixDecNum += num;
            // Since the 'nums' array can be huge, its possible for its decimal
            // equivalent to overflow. Since the prefix computed
            // in ihis iteration is always multiplied by a power of 2 to contribute
            // to the number generated in subsequent iterations; and 2 powers are
            // not divisible by 5; the number can be replaced by its remainder on
            // dividing by 5 for divisiblity checks in succeeding iterations
            prefixDecNum = prefixDecNum % 5;
            // Check for divisibility by 5 of current prefix decimal equivalent
            outV.push_back((0 == prefixDecNum));
        }
        
        return outV;
    }
};
