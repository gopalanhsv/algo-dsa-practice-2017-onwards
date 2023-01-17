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
            // equivalent to overflow. 
            // Since prefixDecNum = 5 * Quotient + Rem in this iteration,
            // for next & subsequent iterations we have
            // the computed prefix number = prefixDecNum * power of 2 + binary digit
            // = (5 * power of 2 * Quotient) + (power of 2 * Rem) + digit
            // For divisibility checks by 5, the first term is irrelevant
            // The number can be replaced by its remainder for succeeding iterations
            prefixDecNum = prefixDecNum % 5;
            // Check for divisibility by 5 of current prefix decimal equivalent
            outV.push_back((0 == prefixDecNum));
        }
        
        return outV;
    }
};
