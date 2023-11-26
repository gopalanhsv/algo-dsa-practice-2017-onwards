// r => num rows, c => num cols
// Time complexity : O(rc + rclogc)
// Space complexity : O(logc)
class Solution {
public:
    int
    largestSubmatrix(vector<vector<int>>& matrix) {
        auto nr = matrix.size();
        auto nc = matrix[0].size();
        
        // Adopt the following greedy approach:-
        // 1. Iterate over each matrix row from top to bottom.
        // 2. At each row 'r', rearrange the columns s.t. the columns which have the
        // max number of vertical consecutive ones ending in cells of row 'r' are
        // grouped together. This allows area of the largest submatrix of all  1's
        // whose last row is 'r' to be determined
        // 3. Repeat step 3 for each row
        
        // At each row, to line up/rearrange columns with the max number of vertical
        // consecutive 1's ending at that row, do the following
        // 1. Determine the number vertical consecutive 1's ending at each cell
        // at that row => Column cells of vertical consecutive 1's get represented
        // virtually by aa single value
        // 2. Sort the values obtained in step 1 above in non-decreasing order
        // This is akin to rearranging/grouping columns with max number of consecutive
        // 1's ending in cells of row 'r' together
        
        // For each column, determine the number vertical consecutive 1's
        // ending at a particular cell and update same
        for (auto c = 0; c != nc; ++c) {
            int nConsecOnes = 0;
            for (auto r = 0; r != nr; ++r) {
                if (1 == matrix[r][c]) {
                    ++nConsecOnes;
                } else {
                    nConsecOnes = 0;
                }
                matrix[r][c] = nConsecOnes;
            }
        }
        
        auto largestSubMatrixArea = 0;
        for (auto r = 0; r != nr; ++r) {
            // Sort each matrix row in non-increasing order to virtually group together columns
            // with the max number of vertical consecutive 1's ending at that row.
            auto & rowV = matrix[r];
            sort(rowV.begin(), rowV.end(), greater<int>());
            
            // Iterate over each column in row 'r' from L->R
            auto minVerticalConsecOnesSeen = rowV[0];
            for (auto c = 0; c != nc; ++c) {
                minVerticalConsecOnesSeen =
                    min(minVerticalConsecOnesSeen, matrix[r][c]);
                // Compute area of submatrix of all ones (post column rearrangement) which having row 'r'
                // as bottom row, col 'c' as rightmost column, column '0' as leftmost column
                auto allOnesSubMatArea = (c + 1) * minVerticalConsecOnesSeen;
                largestSubMatrixArea = max(largestSubMatrixArea, allOnesSubMatArea);
            };
        }
        
        return largestSubMatrixArea;
    }
};
