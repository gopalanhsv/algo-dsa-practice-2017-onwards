// n => differences.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    numberOfArrays(vector<int>& differences, int lower, int upper) {
        auto n = differences.size();
        // If 'f' and 'l' are first and last terms of hidden sequence respectively;
        // the sequence would consist of elements 
        // 1st = f
        // 2nd = f + d[0]
        // 3rd = f + d[0] + d[1]
        // 4th = f + d[0] + d[1] + d[2]
        // 5th = f + d[0] + d[1] + d[2] + d[3]
        // ....................................
        // ith = f + d[0] + d[1] + d[2] + ..... + d[i - 2]
        // ................................................
        // (n + 1)th = l = f + d[0] + d[1] + d[2] + ..... + d[n - 1]
        //  => l = f + sum(differences)
        // i.e. lastTerm = firstTerm + sum(differences)

        // Element with min value of the hidden sequence would be
        // f + min value of prefix sum of differences
        // Element with max value of the hidden sequence would be
        // f + max value of prefix sum of differences
        long pfxSum = 0;
        long maxPfxSum = pfxSum;
        long minPfxSum = pfxSum;
        for (auto & diff : differences) {
            pfxSum += diff;
            maxPfxSum = max(maxPfxSum, pfxSum);
            minPfxSum = min(minPfxSum, pfxSum);
        }
        
        // Hidden sequence element min value should g.e. 'lower';
        // and element max value should be l.e. 'upper'
        // first term + minPfxSum >= lower
        // first term + maxPfxSum <= upper
        // => lower - minPfxSum <= first term <= upper - maxPfxSum
        // => Range of possible first terms of the hidden sequence is
        // [lower - minPfxSum, upper - maxPfxSum]
        // Each of the different values of the first terms gives rise to a 
        // new hidden sequence satifying the given constraints => 
        // num of possible hidden sequences is the number of first terms
        return max(0L, (long)upper - maxPfxSum - lower + minPfxSum + 1);
    }
};
