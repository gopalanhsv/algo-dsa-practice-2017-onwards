// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    int
    findMaxK(vector<int>& nums) {
        unordered_set<int> seenVals;
        int maxVal = 0;
        // Iterate over the array elements sequentially
        for (auto & num : nums) {
            if (seenVals.find(-num) != seenVals.end()) {
                // Current number 'num' and its negation '-num' are present in array
                int val = num > 0 ? num : -num;
                // Update the max value seen (which has its negation in array)
                maxVal = max(maxVal, val);
            }
            seenVals.insert(num);
        }
        
        return (maxVal == 0) ? -1 : maxVal;
    }
};
