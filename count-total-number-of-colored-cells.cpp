// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    long long
    coloredCells(int n) {
        // After 'n' minutes, when we move from the topmost colored row to the
        // lowermost colored row, the structure forms a pyramid of colored cells
        // as follows:-
        // Row 1 has 1 colored cell
        // Row 2 has 3 colored cells
        // Row 3 has 5 colored cells
        // Row 4 has 7 colored cells
        // Row 5 has 9 colored cells
        // .........................
        // .........................
        // Row i has 2i - 1 colored cells
        // .........................
        // .........................
        // Row i has 2i - 1 colored cells
        // .........................
        // .........................
        // Row 'n - 1' (i.e row above middle row) has 2(n - 1) - 1 colored cells
        
        // Row 'n' (i.e middle row) has 2n - 1 colored cells
        
        // The next/bottom 'n - 1' rows form an inverted pyramid structure
        // of rows 1 to 'n - 1' above the middle row 'n'
        
        // So the number of colored cells in rows '1' to 'n - 1' are identical
        // Also the colored cells in form an Arithmetic Progression
        // (1st term = 1; last term = 2(n - 1) - 1; num terms = n - 1)
        
        // Number of colored cells in top & bottom halves/pyramid around middle row 'n'
        long long nColoredCellsInTopAndBottomPyramid = 
            (long long) (1 + 2*(n - 1) - 1) * (n - 1);
        
        long long nColoredCellsInMiddleRow = 2 * n - 1;
        
        return nColoredCellsInTopAndBottomPyramid + nColoredCellsInMiddleRow;
    }
};
