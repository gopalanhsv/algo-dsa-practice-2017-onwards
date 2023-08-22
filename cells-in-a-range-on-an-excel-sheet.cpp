 // Time complexity : num rows x num cols (i.e. number of cells) / O(ncells)
// Space complexity : O(1) excluding output
class Solution {
public:
    vector<string>
    cellsInRange(string s) {
        // Start & end row & col from string
        auto sCol = s[0];
        auto eCol = s[3];
        auto sRow = s[1];
        auto eRow = s[4];
        
        vector<string> rangeCellsV;
        // Iterate over the cells in column major fashion;
        // i.e. all rows in 1st col -> all rows in 2nd col -> all rows in 3rd col and so on
        for (auto col = sCol; col <= eCol; ++col) {
            // 2 char string describing cell belonging to the column 'col'
            string cell(2, col);
            for (auto row = sRow; row <= eRow; ++row) {
                // Update the 2nd char of string describing cell to
                // current 'row' value
                cell[1] = row;
                // Add the cell description to output vector
                rangeCellsV.emplace_back(cell);
            }
        }
        
        return rangeCellsV;
    }
};
