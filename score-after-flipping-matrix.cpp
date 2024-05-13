// p => grid.size(), q => grid[0].size()
// Time complexity : O(pq)
// Space complexity : O(1)

class Solution {
public:
    int
    matrixScore(vector<vector<int>>& grid) {
        // Each row of the grid represents a binary number. Score is the sum of
        // these binary numbers
        // To get highest possible score, maximize the sum of these binary numbers
        
        // For each number, higher order significant digits contribute more to
        // the sum than the lower order significant digits => Adopt the greedy
        // approach of always maximizing the number of set higher order significant
        // digits => maximizing the number of '1's in lower numbered cols
        
        int nr = grid.size();
        int nc = grid[0].size();
        
        int sum = 0;
        // Highest significant bit for each number represented by a row is in col '0',
        // It has a higher impact on sum compared to cols [1, nc - 1]
        // Set this bit to 1  for all nums by toggling rows with 0 in col '0'
        // Update the sum
        sum += ((1 << (nc - 1)) * nr);
        
        // Iterate over the remaining bits of each number from L->R (column major)
        for (auto c = 1; c < nc; ++c) {
            // Compute the number of set bits in current digit location for each number
            int nSetBits = 0;
            for (auto r = 0; r < nr; ++r) {
                nSetBits += (grid[r][0] == grid[r][c]);
            }
            // Maximize the number of set bits by toggling current row if reqd
            nSetBits = max(nSetBits, nr - nSetBits);
            // Update sum
            sum += ((1 << (nc - 1 - c)) * nSetBits);
        }
        
        return sum;
    }
};
