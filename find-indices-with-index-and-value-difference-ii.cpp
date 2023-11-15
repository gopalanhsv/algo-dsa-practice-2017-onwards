// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
        auto arrSz = nums.size();
        if (arrSz < indexDifference) {
            return {-1, -1};
        }
        
        // For a number at index 'j', max absolute diff between nums[j] and
        // numbers preceeding it in the range [0, j - 1] is either its absolute
        // diff with maximum number seen in range [0, j - 1] or
        // with minimum number seen in the range [0, j - 1]
        
        // From the above, if i & j are set to obey 'indexDifference' condition
        // i.e i < j and j - i <= indexDifference, max absolute of difference between
        // nums[j] and any nums[i] with 'i' satisfying above condition is
        // max(abs(nums[j] - max number in [0, i]), abs(nums[j] - min number in [0, i]))
        
        // Tracks the running min and max in the range [0, i]
        auto minUptoIndexI = nums[0];
        auto indexIWithMinVal = 0;
        auto maxUptoIndexI = nums[0];
        auto indexIWithMaxVal = 0;
        // Ensure that j >= i + indexDifference
        for (auto j = indexDifference; j < arrSz; ++j) {
            // Maximum possible value of index 'i'
            auto maxIndexI = j - indexDifference;
            // Update max and min values + indices in range [0, i]
            if (minUptoIndexI < nums[maxIndexI]) {
                indexIWithMinVal = maxIndexI;
                minUptoIndexI = nums[maxIndexI];
                
            }
            if (maxUptoIndexI > nums[maxIndexI]) {
                indexIWithMaxVal = maxIndexI;
                maxUptoIndexI = nums[maxIndexI];
            }
            
            // Candidate max absolute diffs possible between current nums[j]
            // and all possible nums[i] in range [0, j - indexDifference]
            auto candidateMaxDiff = abs(minUptoIndexI - nums[j]);
            if (candidateMaxDiff >= valueDifference) {
                // Found a pair satisfying specified index+value constraint
                return {indexIWithMinVal, j};
            }
            // Candidate max absolute diffs possible between current nums[j]
            // and all possible nums[i] in range [0, j - indexDifference]
            candidateMaxDiff = abs(maxUptoIndexI - nums[j]);
            if (candidateMaxDiff >= valueDifference) {
                // Found a pair satisfying specified index+value constraint
                return {indexIWithMaxVal, j};
            }
        }
        
        return {-1, -1};
    }
};
