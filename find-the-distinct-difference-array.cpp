// Time complexity : O(nums.size())
// Space complexity : O(nums.size())
class Solution {
public:
    vector<int>
    distinctDifferenceArray(vector<int>& nums) {
        int arrSz = nums.size();
        
        // Hash table tracking the number of distinct suffix elements seen so far
        unordered_set<int> suffixElems;
        vector<int> nSuffixElemsV(arrSz, 0);
        // Iterate over the array from R->L. Compute the number of
        // distinct suffix elements for each array location
        for (int i = arrSz - 1; i >= 0; --i) {
            nSuffixElemsV[i] = suffixElems.size();
            suffixElems.insert(nums[i]);
        }
    
        // Hash table tracking the number of distinct prefix elements seen so far
        unordered_set<int> prefixElems;
        // Iterate over the array from L->R. Compute the number of
        // distinct prefix elements for each array location; and 
        // determine distinct diff value at each index
        vector<int> diffV(arrSz, 0);
        for (int i = 0; i != arrSz; ++i) {
            prefixElems.insert(nums[i]);
            auto nDistinctPrefixElems = prefixElems.size();
            diffV[i] = nDistinctPrefixElems - nSuffixElemsV[i];
        }
        
        return diffV;
    }
};
