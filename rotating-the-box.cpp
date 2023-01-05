class Solution {
public:
    vector<vector<char>>
    rotateTheBox(vector<vector<char>>& box) {
        int nr = box.size();
        int nc = box[0].size();
        
        // After 90deg clockwise rotation, the box gets transposed
        // with the obstacles staying in their original positions;
        // stones falling through empty spaces underneath till blocked
        // by obstacles/stone below/box bottom
        
        // Build the transposed box column by column from
        // the original box. Init to empty spaces
        vector<vector<char> > transBox(nc, vector<char>(nr, '.'));
        for (int c = 0; c != nr; ++c) {
            // Column 'c' of rotated box is built from bottom to top;
            // comprising of elements from row 'nr - 1 - c' of original box
            // from right to left
            int wrRowIdx = nc - 1;
            for (int r = nc - 1; r >= 0; --r) {
                if (box[nr - 1 - c][r] == '*') {
                    // Obstacle stays put
                    transBox[r][c] = '*';
                    wrRowIdx = r - 1;
                } else if (box[nr - 1 - c][r] == '#') {
                    // Stone moves down till blocked by another stone/
                    // box bottom or obstacle
                    transBox[wrRowIdx--][c] = '#';
                }
            }
        }
        
        return transBox;
    }
};
