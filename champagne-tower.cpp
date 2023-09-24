//  r => query_row, c => query_glass
// DP Approach
// Time complexity : O(rc)
// Space complexity : O(rc)

// DP Approach Optimized
// Time complexity : O(rc)
// Space complexity : O(c)

class Solution {
public:
    double
    champagneTower(int poured, int query_row, int query_glass) {   
        //return champagneTowerBottomUpDPApproach(poured, query_row, query_glass);   
        return champagneTowerBottomUpDPApproachSpaceOptimized(poured, query_row, query_glass);
    }

private:
    
    double
    champagneTowerBottomUpDPApproach(int poured, int query_row, int query_glass) {
        if (0 == poured) {
            // Base case of no champagne poured => all glasses are empty
            return 0.0;
        }
        
        // The 'i'th glass (1-indexed from left to right) at row 'r' (1-indexed from top
        // to bottom) the pyramid is represented as being at the location (r - 1, i - 1)
        
        // When a glass overflows, liquid falls to the glasses placed immediately below
        // it on either side. Since glasses are arranged in pyramid formation, for each row
        // 'r' (1-indexed) there are only 'r' glasses in total. Overflowing happens
        // in symmetrical Pascal triangle formation
        
        // Computation needs to done till 'query_row' (which will have 'query_row'
        // glasses and each row above this will have progressively lesser number of glasses)
        int nr = query_row;
        int nc = nr;
        // dpTbl[r][c] is the amount of champagne in the cup at location (r, c) after
        // 'poured' quantity of champagne is poured into the top glass at location (0, 0)
        vector<vector<double> > dpTbl(nr + 1, vector<double>(nc + 1, 0.0));

        // Initialize
        dpTbl[0][0] = poured;
        
        // Iterate from top row down to query row sequentially 
        for (int r = 0; r < nr; ++r) {
            // Flag tracking overflow event from any glass in current row
            // to the next row immediately below
            bool noOverflowToNextRowGlasses = true;
            // Iterate over each glass in the current row from left onwards
            for (int c = 0; c <= r; ++c) {
                if (dpTbl[r][c] > 1.0) {
                    // Excess champagne in current glass overflows in equal amount to
                    // the 2 glasses on either side placed in the next row immediately below
                    double halfOfOverflowQty = (dpTbl[r][c] - 1.0) / 2;
                    noOverflowToNextRowGlasses = false;
                    dpTbl[r + 1][c] += halfOfOverflowQty;
                    dpTbl[r + 1][c + 1] += halfOfOverflowQty;
                }
            }
            if (noOverflowToNextRowGlasses) {
                // No more overflowing to the next row => all rows of glasses from
                // next row onwards will be empty
                break;
            }
        }
        
        // Normalize for excess champagne in the queried glass
        return min(1.0, dpTbl[query_row][query_glass]);
    }

    double
    champagneTowerBottomUpDPApproachSpaceOptimized(
        int poured, int query_row, int query_glass) {

        if (0 == poured) {
            // Base case of no champagne poured => all glasses are empty
            return 0.0;
        }
        
        // The 'i'th glass (1-indexed from left to right) at row 'r' (1-indexed from top
        // to bottom) the pyramid is represented as being at the location (r - 1, i - 1)
        
        // When a glass overflows, liquid falls to the glasses placed immediately below
        // it on either side. Since glasses are arranged in pyramid formation, for each row
        // 'r' (1-indexed) there are only 'r' glasses in total. Overflowing happens
        // in symmetrical Pascal triangle formation
        
        // Computation needs to done till 'query_row' (which will have 'query_row'
        // glasses and each row above this will have progressively lesser number of glasses)
        int nr = query_row;
        int nc = nr;
        // dpTbl[r][c] is the amount of champagne in the cup at location (r, c) after
        // 'poured' quantity of champagne is poured into the top glass at location (0, 0)
        
        // Since computation of champagne in the glasses for each row depends only on the 
        // the values in the glasses in the preceeding row, need only 2 rows in the table
        // and use modulo-2 divison to switch between the current and next row
        vector<vector<double> > dpTbl(2, vector<double>(nc + 1, 0.0));

        // Initialize
        dpTbl[0][0] = poured;
        
        // Iterate from top row down to query row sequentially 
        for (int r = 0; r < nr; ++r) {
            // Iterate over each glass in the current row from left onwards
            // Init the values for the next row (as the table is being reused)
            for (int c = 0; c <= r; ++c) {
                dpTbl[((r + 1) & 0x1)][c] = 0.0;   
            }
            for (int c = 0; c <= r; ++c) {
                if (dpTbl[(r & 0x1)][c] > 1.0) {
                    // Excess champagne in current glass overflows in equal amount to
                    // the 2 glasses on either side placed in the next row immediately below
                    double halfOfOverflowQty = (dpTbl[(r & 0x1)][c] - 1.0) / 2;
                    dpTbl[((r + 1) & 0x1)][c] += halfOfOverflowQty;
                    dpTbl[((r + 1) & 0x1)][c + 1] += halfOfOverflowQty;
                }
            }
            
            // Not using overflow flags as table is being re-used and usage of
            // same dirties locations which should be 0.0 in nonspace-optimized approach
        }
        
        // Normalize for excess champagne in the queried glass
        return min(1.0, dpTbl[(query_row & 0x1)][query_glass]);
    }
};
