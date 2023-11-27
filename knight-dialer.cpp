// DP Approach
// Time complexity : O(10n) => O(n)
// Space complexity : O(10n) => O(n)

// DP Approach Space Optimized
// Time complexity : O(10n) => O(n)
// Space complexity : O(10) => O(1)

class Solution {
public:
    int
    knightDialer(int n) {
        //return knightDialerBottomUpDP(n);
        return knightDialerBottomUpDPSpaceOptimized(n);
    }
    
private:
    
    int
    knightDialerBottomUpDP(int n) {
        // sourceCellsTbl[x] gives the list of cells from which cell 'x'
        // can be reach on the dialing pad via knight moves
        vector< vector<int> > sourceCellsTbl(10);
        sourceCellsTbl[0] = {4, 6};
        sourceCellsTbl[1] = {8, 6};
        sourceCellsTbl[2] = {9, 7};
        sourceCellsTbl[3] = {4, 8};
        sourceCellsTbl[4] = {3, 9, 0};
        sourceCellsTbl[5] = {};
        sourceCellsTbl[6] = {1, 7, 0};
        sourceCellsTbl[7] = {2, 6};
        sourceCellsTbl[8] = {1, 3};
        sourceCellsTbl[9] = {4, 2};
        
        // dpTbl[j][d] is the number of distinct ways in which the 'd' cell/digit
        // of the dial can be reached/dialed in 'j - 1' knight jumps, i.e. number of
        // distinct numbers of 'j' digits with last digit as 'd'
        vector<vector<long> > dpTbl(n + 1, vector<long>(10, 0));
        // For a number of length '1', any digit 'd' can be dialed directly
        // by placing the knight over same 'd' i.e. in 1 way
        for (auto d = 0; d <= 9; ++d) {
            dpTbl[1][d] = 1;
        }
        
        const int moduloFactor = 1000000000 + 7;
        // Iterate over the number lengths sequentially from 2 to 'n'
        for (auto l = 2; l <= n; ++l) {
            // Iterate over all possible digits [0, 9] for current
            // number of length 'l' 
            for (auto d = 0; d <= 9; ++d) {
                // Determine the count of distinct nums of length 'l'
                // digits ending with digit 'd'
                long nCount = 0;
                // Number of length 'l' with last digit 'd' can be made by
                // appending digit 'd' to those numbers of length 'l - 1'
                // whose last digit allows 'd' to be reached via knight 
                // move in a single hop
                for (auto & sd : sourceCellsTbl[d]) {
                    nCount += dpTbl[l - 1][sd];
                    nCount %= moduloFactor;
                }
                dpTbl[l][d] = nCount;
            }
        }
        
        // Add up the count of distinct numbers of 'n' digits possible with
        // last digit as any in range [0, 9] to determine the total count
        long nTotalDistinctNums = 0;
        for (auto d = 0; d <= 9; ++d) {
            nTotalDistinctNums += dpTbl[n][d];
            nTotalDistinctNums %= moduloFactor;
        }
        return nTotalDistinctNums;
    }
    
    int
    knightDialerBottomUpDPSpaceOptimized(int n) {
        // sourceCellsTbl[x] gives the list of cells from which cell 'x'
        // can be reach on the dialing pad via knight moves
        vector< vector<int> > sourceCellsTbl(10);
        sourceCellsTbl[0] = {4, 6};
        sourceCellsTbl[1] = {8, 6};
        sourceCellsTbl[2] = {9, 7};
        sourceCellsTbl[3] = {4, 8};
        sourceCellsTbl[4] = {3, 9, 0};
        sourceCellsTbl[5] = {};
        sourceCellsTbl[6] = {1, 7, 0};
        sourceCellsTbl[7] = {2, 6};
        sourceCellsTbl[8] = {1, 3};
        sourceCellsTbl[9] = {4, 2};
        
        // dpTbl[j][d] is the number of distinct ways in which the 'd' cell/digit
        // of the dial can be reached/dialed in 'j - 1' knight jumps, i.e. number of
        // distinct numbers of 'j' digits with last digit as 'd'
        // Since calculation for a particular number length 'l', depends only on the
        // calculation done for number length 'l - 1' in previous iteration, use an
        // array of with 2 rows instead of 'n'; and flip between the rows with one
        // row being used for current computation while referring to the other row
        // for previous computation via modulo-2 ops
        vector<vector<long> > dpTbl(2, vector<long>(10, 0));
        // For a number of length '1', any digit 'd' can be dialed directly
        // by placing the knight over same 'd' i.e. in 1 way
        for (auto d = 0; d <= 9; ++d) {
            dpTbl[1][d] = 1;
        }
        
        const int moduloFactor = 1000000000 + 7;
        // Iterate over the number lengths sequentially from 2 to 'n'
        for (auto l = 2; l <= n; ++l) {
            // Iterate over all possible digits [0, 9] for current
            // number of length 'l' 
            for (auto d = 0; d <= 9; ++d) {
                // Determine the count of distinct nums of length 'l'
                // digits ending with digit 'd'
                long nCount = 0;
                // Number of length 'l' with last digit 'd' can be made by
                // appending digit 'd' to those numbers of length 'l - 1'
                // whose last digit allows 'd' to be reached via knight 
                // move in a single hop
                for (auto & sd : sourceCellsTbl[d]) {
                    nCount += dpTbl[(l - 1) & 0x1][sd];
                    nCount %= moduloFactor;
                }
                dpTbl[(l & 0x1)][d] = nCount;
            }
        }
        
        // Add up the count of distinct numbers of 'n' digits possible with
        // last digit as any in range [0, 9] to determine the total count
        long nTotalDistinctNums = 0;
        for (auto d = 0; d <= 9; ++d) {
            nTotalDistinctNums += dpTbl[(n & 0x1)][d];
            nTotalDistinctNums %= moduloFactor;
        }
        return nTotalDistinctNums;
    }
};
