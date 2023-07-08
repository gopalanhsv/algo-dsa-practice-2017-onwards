// w => weights.size()
// Time complexity : O(wlogw)
// Space complexity : O(w)
class Solution {
public:
    long long
    putMarbles(vector<int>& weights, int k) {
        // The problem does not mention that ALL the marbles get
        // distributed amongst the 'k' bags -- this is a requirement
        // Cost of bag which includes all marbles in the subarray [i, j] is weights[i] + weights[j],
        // i.e. sum of marble weights at the subarray/bag extremities[i, j]
        int arrSz = weights.size();
        if (arrSz <= k) {
            // Base case of array size being l.e the number of required partitions/bags 
            return 0;
        }
        
        // The distribution problem reduces to partitioning the array into 'k' subarrays
        // in the following 2 ways :-
        // 1. Partition #1 should result in k subarrays; s.t sum of the 2 elements at the
        // subarray extremities over all subarrays results in max possible score
        // 2. Partition #2 should result in k subarrays; s.t sum of the 2 elements at the
        // subarray extremities over all subarrays results in min possible score
        // Both of the above require the selection of 'k - 1' partition points between
        // indices 0 and 'arrSz - 1' (these 2 points are selected by default)
        
        // There are a total of 'arrSz - 1' partition points at which the array can be
        // partitioned. Of these 'k - 1' points need to be selected separately s.t. one gets
        // partition #1 with one selection and partition #2 with the other selection.
        // Say the current score of array A with some partitioning (l.t. k partitions) is 'S'.
        // And additional new partitioning after an index 'i', results in new subarray ending
        // at index 'i' and a new one starting at index 'i + 1'. This increases the score
        // to S + A[i] + A[i + 1]. Each partitioning after a new index 'x' increases the
        // score by A[x] + A[x + 1].
        
        // Current array has 'arrSz - 1' partition points/indices at 0, 1, 2, ..., arrSz - 2
        // Partitioning immediately after these points increases the score by 
        // A[0] + A[1], A[1] + A[2], A[2] + A[3], ...A[i] + A[i + 1]...A[arrSz - 2] + A[arrSz - 1]
        // respectively
        
        // For max score, adopt greedy approach of selecting 'k - 1' partition points/indices
        // from the above leading to max increase in score => choose 'k - 1' scores from the
        // possible 'arrSz - 1' scores with the maximum value
        // For min score, adopt greedy approach of selecting 'k - 1' partition points/indices
        // from the above leading to min increase in score => choose 'k - 1' scores from the
        // possible 'arrSz - 1' scores with the minimum value
        
        // Above is easily doable via sorting
        vector<long long> scoreIncrementsV;
        // Iterate over possible partition points
        for (int i = 0; i <= arrSz - 2; ++i) {
            // Score increment due to partitioning immediately after index 'i'
            long long delta = weights[i] + weights[i + 1];
            // Add the score to the array of possible increments
            scoreIncrementsV.emplace_back(delta);
        }
        
        // Sort the potential score increments
        sort(scoreIncrementsV.begin(), scoreIncrementsV.end());
        // Select 'k - 1' scores from beginning of sorted increments for min score
        // Select 'k - 1' scores from ending of sorted increments for max score
        // Skipping the '0' & 'arrSz - 1' values as they get cancelled out on diff
        long long maxScoreDelta = 0, minScoreDelta = 0;
        for (int i = 0; i <= k - 2; ++i) {
            minScoreDelta += scoreIncrementsV[i];
            maxScoreDelta += scoreIncrementsV[arrSz - 2 - i];
        }
        
        return maxScoreDelta - minScoreDelta;
    }
};
