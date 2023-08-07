// Time complexity : O(num rows + num cols)
// Space complexity : O(1)
class Solution {
public:
    bool
    searchMatrix(vector<vector<int>>& matrix, int target) {

        // The matrix is structured such that elements are ordered in ascending order
        // from L->R in each row. For a particular col, element in a row is greater
        // than element in preceeding row. The above implies that in each row, elements
        // are in ascending order from L->R and for each col elements are in ascending
        // order from top to bottom
        
        // Init num matrix rows/cols
        int nr = matrix.size();
        int nc = matrix[0].size();
        
        // Base case of empty matrix
        if ((0 == nr) || (0 == nc)) {
            return false;
        }

        // Since matrix elements are ordered in ascending order both row and column
        // wise; smallest element is at top left and largest element at bottom right
        if ((target < matrix[0][0]) ||
            (target > matrix[nr - 1][nc - 1])) {
            // 'target' element out of matrix range
            return false;
        }
        
        // The matrix degenerates to a sorted array of elements in ascending order
        // if we scan each row from L->R; then move to 1st element in next row to
        // repeat the scan. So idea should be to employ binary search on rows and
        // cols s.t the location of element can be pinpointed. So find we just need
        // to find a traversal s.t. if element being lesser/more than target cuts down
        // the search space; and does not require backtracking/revisit of a search
        // space. Top right corner to bottom left corner movement satisfies this.
        // Examine element at (r, c) commencing from top right. If lesser than target,
        // move to immediate left column and repeat. If more than target, move
        // vertically down to next row and repeat. Do till target found or space is
        // exhausted. 
        // The procedure can be done also by similar movement from bottom left to
        // top right. Will implement the 2nd option of bottom left to top right
        // search space reduction technique here
        int c = 0;
        int r = nr - 1;
        while ((r >= 0) && (c < nc)) {
            auto elem = matrix[r][c];
            if (elem == target) {
                // Found 'target'
                return true;
            }
            
            if (elem > target) {
                // Current element exceeds 'target'; search in direction
                // of lesser element values. 'target' is lesser than elements
                // in rows below from where we have come; so move 
                // vertically up for lesser element values)
                --r;
            } else {
                // Current element l.t 'target'; search in direction of
                // larger element values. 'target' is more than elements
                // in left columns from where we have come; so move 
                // horizontally right for larger element values)
                ++c;
            }
        }
        
        return false;    
    }
};
