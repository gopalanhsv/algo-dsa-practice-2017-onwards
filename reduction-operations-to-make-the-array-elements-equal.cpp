// n => nums.size()

// Approach1
// Time complexity : O(nlogn)
// Space complexity : O(n)

// Approach2
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    int
    reductionOperations(vector<int>& nums) {
        
        //return reductionOperationsApproach1(nums);
        return reductionOperationsApproach2(nums);
    }
    
private:

    int
    reductionOperationsApproach1(vector<int>& nums) {
        // At any point in time during the reductions operation, smallest index with the
        // current array maximum gets reduced to the second maximum, till all nums are same.
        // => the smallest index is immaterial as all instances of maximum value get
        // reduced to the second maximum => num instances of current array maximum
        // reduction operations are required to reduce all maximums to the second maximums
        
        // => Maintain frequency count of each number and organize the numbers from
        // largest to smallest
        map<int, int, greater<int> > freqCntTbl;
        for (auto & num : nums) {
            freqCntTbl[num]++;
        }
        
        int nOps = 0;
        // Iterate over the frequency count table from largest to smallest number
        // sequentially, reducing the current maximum to the second maximum at each
        // step till all array elements are equal (i.e at the array minimum)
        auto minElem = (freqCntTbl.rbegin())->first;
        auto iter = freqCntTbl.begin();
        auto currMaxElem = iter->first;
        while (currMaxElem != minElem) {
            // All current maximum get reduced to the second maximums
            auto & nCurrMaxElems = iter->second;
            nOps += nCurrMaxElems;
            // Update the occurence count of the second maximum to account for
            // reduction of array maximum to second maximum
            ++iter;
            iter->second += nCurrMaxElems;
            // Update current maximum to the second maximum
            currMaxElem = iter->first;
        }
        
        return nOps;
    }

    int
    reductionOperationsApproach2(vector<int>& nums) {
        // At any point in time during the reductions operation, smallest index with the
        // current array maximum gets reduced to the second maximum, till all nums are same.
        // => the smallest index is immaterial as all instances of maximum value get
        // reduced to the second maximum => num instances of current array maximum
        // reduction operations are required to reduce all maximums to the second maximums
        
        // Sort the nums in descending order
        sort(nums.begin(), nums.end(), greater<int>());
        
        int nOps = 0;
        // Iterate over the sorted nums from largest to smallest number sequentially,
        // reducing all instances of the current maximum to the second maximum at each
        // step till all array elements are equal
        auto n = nums.size();
        auto nCurrMaxElems = 1;
        for (auto i = 1; i != n; ++i) {
            if (nums[i] < nums[i - 1]) {
                // 2nd maximum hit as array is sorted in descending order and current 
                // element is l.t previous
                // Reduce all the current maximums to the second maximums
                nOps += nCurrMaxElems;
            }
            // All the previous array maximums become current maximum nums[i]
            ++nCurrMaxElems;
        }
        
        return nOps;
    }
};
