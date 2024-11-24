// p => matrix.size(), q => matrix[0].size()
// Time Complexity : O(pq)
// Space Complexity : O(1)

class Solution {
public:
    long long
    maxMatrixSum(vector<vector<int>>& matrix) {
        
        // For each row, all -ve sign can be moved to one corner by successively
        // multiplying adjacent elements by -1 to shift sign. All -ve elements
        // present in disjoint groups of 2 adjacent elements are made +ve
        // In essence, if there are even -ve elements in a row, all of them
        // become +ve; and if there odd number of -ve elements in a row, all of
        // them except 1 become +ve.
        
        // Above operations are applied row-wise and then column-wise to convert
        // the max number of -ve elements to +ve except at most 1 element.
        // If the matrix has even number of -ve elements, all become +ve & if it
        // has odd number of -ve elements, all except one become +ve. So, the matrix is left
        // with at most one -ve element after the successive application of said operations
        
        // Now matrix sum is maximum when all/maximum elements are +ve
        // => The sole remaining -ve sign (in case of matrix with odd number of
        // -ve elements) should be moved to the element with least contribution to
        // the matrix sum i.e. the element with least magnitude in the matrix
        
        bool oddNumNegatives = false;
        long long maxSum = 0;
        // Iterate over each matrix element. Compute the max possible matrix sum
        // (assuming all +ve elements) and track the minimum magnitude element
        auto nr = matrix.size();
        auto nc = matrix[0].size();
        int minMagnitudeElem = numeric_limits<int>::max();
        for (auto r = 0; r < nr; ++r) {
            for (auto c = 0; c < nc; ++c) {
                auto elem = matrix[r][c];
                if (elem < 0) {
                    oddNumNegatives = !oddNumNegatives;
                    elem = -elem;
                }
                maxSum += elem;
                minMagnitudeElem = min(minMagnitudeElem, elem);
            }
        }

        // Sole remaining -ve sign applied to minimum magnitude element
        // (subtracted twice to account for adding it earlier)
        if (oddNumNegatives) {
            maxSum -= (2 * minMagnitudeElem);
        }
        return maxSum;
    }
};
