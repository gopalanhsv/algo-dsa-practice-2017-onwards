// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    long long
    countBadPairs(vector<int>& nums) {
        // Bad pair if i < j and j - i != nums[j] - nums[i]
        // => nums[i] - i != nums[j] - j
        // Create a diff vector diffV[x] = nums[x] - x for each element of 'nums'
        
        // For bad pairs diffV[i] != diffV[j] fo5r all i < j
        // Since diffV[i] != diffV[j] is same as diffV[j] != diffV[i]
        // i < j is just noise other than the fact that i != j
        
        // Problem reduces to determining the count of pairs for which 
        // diffV[i] != diffV[j] for i != j
        // Bad pairs are formed only between numbers having different 'diff' values
        
        // Build a hash table of diff values mapped to the occurence/frequency count
        // of numbers having the respective frequency counts
        auto arrSz = nums.size();
        unordered_map<int, long long> diffs2FreqCntTbl;
        for (auto i = 0; i != arrSz; ++i) {
            // Diff value of nums at current index
            auto diffVal = nums[i] - i;
            diffs2FreqCntTbl[diffVal]++;
        }
        
        long long nBadPairs = 0;
        // Iterate over the diffs table
        for (auto & ent : diffs2FreqCntTbl) {
            // Numbers with diff val 'ent.first' occurence count
            auto cnt = ent.second;
            // Numbers with current diff val 'diff.first' form bad
            // pairs with numbers having a different diff val
            long long nOtherNumsCnt = arrSz - cnt;
            // Compute number of bad pairs formed by numbers with current diff
            // value with the other numbers having a different diff value
            nBadPairs += (cnt * nOtherNumsCnt);
        }
        
        // Halving to account for duplicate calcs
        nBadPairs /= 2;
        return nBadPairs;
    }
};
