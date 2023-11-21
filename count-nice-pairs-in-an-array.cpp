// M => max number in 'nums', n => nums.size()
// Time complexity : O(nlogM)
// Space complexity  : O(n)

class Solution {
public:
    int
    countNicePairs(vector<int>& nums) {
        int n = nums.size();
        // For all nice pairs, 0 <= i < j < n
        // nums[i] + rev(nums[j]) == nums[j] + rev(nums[i])
        // The above implies that for nice pairs, we require
        // nums[i] - rev(nums[i]) == nums[j] - rev(nums[j])

        // Maintain a hash table tracking frequency count of difference between a number
        // and its reverse "nums[i] - rev(nums[i])" at each index 0 <= i < n
        // Numbers at different indices which have the same value of differences
        // between number and its reverse form nice pairs with each other
        unordered_map<int, long> diffFreqCntTbl;
        const int moduloFactor = 1000000000 + 7;
        long totalNicePairs = 0;
        // Iterate over the array entries sequentially from L->R
        // (That will take care of constraint i < j)
        for (auto & num : nums) {
            // Compute difference between number and its reverse
            int diff = num - numberReversed(num);
            // Check if current number forms a nice pair with
            // a number seen earlier in the array (numbers at pair
            // indices will have same diff values)
            auto iter = diffFreqCntTbl.find(diff);
            if (iter != diffFreqCntTbl.end()) {
                // Current index forms a nice pair with indices seen
                // earlier in the array which would be the frequency
                // count of same diffs seen earlier
                long int nPairs = iter->second;
                
                // Update total number of nice pairs
                totalNicePairs += nPairs;
                totalNicePairs %= moduloFactor;
            }
            
            // Update the frequency count table for diff value
            diffFreqCntTbl[diff]++;
        }
        
        return totalNicePairs;
    }
    
    
private:
    
    inline int
    numberReversed(int n) {
        int revNum = 0;
        while (n > 0) {
            revNum = (10 * revNum) + (n % 10);
            n /= 10;
        }
        
        return revNum;
    }
};
