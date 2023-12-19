// nr => Num image rows, nc => Num image cols
// Time complexity : O(nr x nc)
// Space complexity : O(1)

class Solution {
public:
    vector<vector<int>>
    imageSmoother(vector<vector<int>>& img) {
        // Since each cell stores values in range [1,255]; the result of
        // the smoothed average will also be in the range [1, 255]. This 
        // result and original value requires 8 bits.
        
        // We can save space by reusing the image cells (32 bit int) to store the result
        // as follows. Use the lower 8 bits (least / significant 8 bits[0, 7] during
        // average computation/smoothing); and store the result/average for each cell in
        // the most significant bits (i.e. bits[31, 8]). After smoothing has be done for
        // each cell; shift the contents of each cell to the right by 8 bits; so that
        // each cell has its value overwritten by the smoothed value
        
        if (img.empty() || img[0].empty()) {
            // Empty input vector
            return img;
        }
        
        // Init num rows and cols
        int nr = img.size();
        int nc = img[0].size();
        const int filterCellValMask = 0xFF;
        const int filterCellShift = 8;
        
        // Iterate over each cell in row major fashion
        for (auto r = 0; r != nr; ++r) {
            for (auto c = 0; c != nc; ++c) {
                
                // Compute valid ranges of surrounding cells for a 3x3 sized filter
                auto minRow = max(0, r - 1);
                auto maxRow = min(nr - 1, r + 1);
                auto minCol = max(0, c - 1);
                auto maxCol = min(nc - 1, c + 1);
                // Compute the sum of all cells in 3x3 filter centred at (r, c)
                auto filterCellSum = 0;
                auto nFilterCells = 0;
                for (auto r1 = minRow; r1 <= maxRow; ++r1) {
                    for (auto c1 = minCol; c1 <= maxCol; ++c1) {
                        filterCellSum += (filterCellValMask & img[r1][c1]);
                        ++nFilterCells;
                    }   
                }
                // Store filter average in the upper bits [31, 8]
                img[r][c] |= ((filterCellSum / nFilterCells) << filterCellShift);
            }
        }
        
        // Update all the image values to the smoothed filter values
        for (int r = 0; r != nr; ++r) {
            for (int c = 0; c != nc; ++c) {
                // Move stored filter average to the lower bits [7, 0]
                img[r][c] >>= filterCellShift;
            }
        }
        
        return img;
    }
};
