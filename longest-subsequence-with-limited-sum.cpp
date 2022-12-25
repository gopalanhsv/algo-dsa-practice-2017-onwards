class Solution {
public:
    vector<int>
    answerQueries(vector<int>& nums, vector<int>& queries) {
        
        // For a subsequence of a sequence to be of the maximum size
        // possible, s.t. all the subsequence elements are lesser/equal
        // to a given value; the subsequence should comprise of
        // smallest elements from the given sequence satisfying the
        // given constraints
        
        // The above implies that for each sum/query, keep selecting the
        // minimum elements from the sequence till sum of the selected
        // elements exceeds the given query/sum. The selected set would
        // be the longest subsequence for the query
        
        // Sort nums in non-decreasing order (in order to select the set
        // of smallest number adding upto a query value)
        sort(nums.begin(), nums.end());

        // Instead of finding the longest sequence adding upto a given query/sum
        // each time linearly by adding up the numbers; we can do a
        // cumulative/prefix sum for each of the numbers in the sorted
        // sequence and perform a binary search on the cumulative sum array
        
        // Build the prefix/cumulative sum array for each element in
        // sorted array 'nums'
        // i.e. cSumV[i] = sum of each element in closed range [0, i]
        vector<int> cSumV(nums.size(), 0);
        cSumV[0] = nums[0];
        for (int i = 1; i != nums.size(); ++i) {
            cSumV[i] = cSumV[i - 1] + nums[i];
        }
        
        vector<int> answersV;
        // Iterate over each query sum
        for (auto query : queries) {
            // Execute a binary search on the cumulative sum array to find
            // the set of sorted numbers/subsequence which add up to the
            // given query
            auto lbIter = lower_bound(cSumV.begin(), cSumV.end(), query);
            int maxSubSeqLen;
            if (lbIter != cSumV.end()) {
                if ((*lbIter) == query) {
                    ++lbIter;
                }
            }
            maxSubSeqLen = lbIter - cSumV.begin();
            answersV.emplace_back(maxSubSeqLen);
        }
        
        return answersV;
    }
};
