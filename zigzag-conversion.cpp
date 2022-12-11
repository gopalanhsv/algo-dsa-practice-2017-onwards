class Solution {
public:
    string
    convert(string s, int numRows) {
    
        // The output is such that 'numRows' chars are printed in a column
        // where no rows are to be skipped from top, followed by cols 
        // where number of rows to be skipped progressively decreases back
        // to 0. Only one char gets printed in cols where rows are skipped.
        
        // Array of strings, 1 per row
        vector<string> rowStringsV(numRows);
        // The number of rows from top which are to be skipped in current column
        int nRowsToSkippedInCurrCol = 0;
        int sIdx = 0;
        int strSz = s.size();
        while (sIdx < strSz) {
            if (nRowsToSkippedInCurrCol > 0) {
                // Few rows to be skipped. Output single char in the
                // appropriate row
                rowStringsV[nRowsToSkippedInCurrCol] += s[sIdx++];
                // Update the number of rows to be skipped for next column
                --nRowsToSkippedInCurrCol;
            } else {
                // No rows to be skipped, output 1 new char per row
                // in this column
                int rowIdx = 0;
                while ((sIdx < strSz) && (rowIdx < numRows)) {
                    rowStringsV[rowIdx++] += s[sIdx++];
                }
                // Update the number of rows to be skipped for next column
                nRowsToSkippedInCurrCol = numRows - 2;
            }
        }
        
        // Now convert the row based output back to single string form
        sIdx = 0;
        for (auto & rowStr : rowStringsV) {
            for (auto & c : rowStr) {
                s[sIdx++] = c;
            }
        }
        
        return s;
    }
};
