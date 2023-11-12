// Bottom Up DP
// Time complexity : O(nk)
// Space complexity : O(nk)

// Bottom Up DP Space Optimized
// Time complexity : O(nk)
// Space complexity : O(k)

class Solution {
public:
    int
    waysToDistribute(int n, int k) {
        //return waysToDistributeViaBottomUpDp(n, k);
        return waysToDistributeViaBottomUpDpSpaceOptimized(n, k);
    }
    
private:

    int
    waysToDistributeViaBottomUpDp(int n, int k) {
        // nWays(x, b) => is the number of ways to distibuted 'x' unique candies over 'b' bags
        
        // The 'x' candy distributed in 2 ways:-
        // 1. Place in a single bag by itself. Reduces to the the number of ways
        // to distribute remaining 'x - 1' candies over remaining 'b - 1' bags
        // nWays(x - 1, b - 1)
        // 2. Share a bag with any of the 'x - 1' remaining candies i.e. any of the
        // 'b' bags. One of the 'b' bags for placing the 'x'th candy can be selected
        // in 'b' ways => total of b*nWays(x - 1, b)
        
        // => nWays(x, b) = nWays(x - 1, b - 1) + b * nWays(x - 1, b)
        // Base case of nWays(x, 1) = 1 (i.e. 1 bag => only 1 way for candy distribution)
        // and nWays(b, b) = 1 (i.e. only 1 way as a min of 1 candy is reqd per bag and
        // b candies have to be distributed as 1 candy per bag)
        // x >= b by default otherwise it leads to 0 candy in some bag which is not allowed
        // as an input constraint
        
        // dpTbl[x][b] is the number of ways to distributed 'x' unique candies over 'b' bags
        vector<vector<long> > dpTbl(n + 1, vector<long>(k + 1));
        for (int candyCnt = 1; candyCnt <= n; ++candyCnt) {
            if (candyCnt <= k) {
                dpTbl[candyCnt][candyCnt] = 1;
            }
            dpTbl[candyCnt][1] = 1;
        }

        const int moduloFactor = 1000000000 + 7;
        for (int candyCnt = 2; candyCnt <= n; ++candyCnt) {
            for (int nBags = 1; nBags <= min(k, candyCnt); ++nBags) {
                dpTbl[candyCnt][nBags] =
                    dpTbl[candyCnt - 1][nBags - 1] + (nBags * dpTbl[candyCnt - 1][nBags]);
                dpTbl[candyCnt][nBags] %= moduloFactor;
            }
        }
        return dpTbl[n][k];
    }

    int
    waysToDistributeViaBottomUpDpSpaceOptimized(int n, int k) {
        // nWays(x, b) => is the number of ways to distibuted 'x' unique candies over 'b' bags
        
        // The 'x' candy distributed in 2 ways:-
        // 1. Place in a single bag by itself. Reduces to the the number of ways
        // to distribute remaining 'x - 1' candies over remaining 'b - 1' bags
        // nWays(x - 1, b - 1)
        // 2. Share a bag with any of the 'x - 1' remaining candies i.e. any of the
        // 'b' bags. One of the 'b' bags for placing the 'x'th candy can be selected
        // in 'b' ways => total of b*nWays(x - 1, b)
        
        // => nWays(x, b) = nWays(x - 1, b - 1) + b * nWays(x - 1, b)
        // Base case of nWays(x, 1) = 1 (i.e. 1 bag => only 1 way for candy distribution)
        // and nWays(b, b) = 1 (i.e. only 1 way as a min of 1 candy is reqd per bag and
        // b candies have to be distributed as 1 candy per bag)
        // x >= b by default otherwise it leads to 0 candy in some bag which is not allowed
        // as an input constraint
        
        // dpTbl[x][b] is the number of ways to distributed 'x' unique candies over 'b' bags
        // Since each row calc depends only on the previous, use a 2 row table and flip
        // between the rows for each iteration
        vector<vector<long> > dpTbl(2, vector<long>(k + 1));

        const int moduloFactor = 1000000000 + 7;
        for (int candyCnt = 1; candyCnt <= n; ++candyCnt) {
            
            // Init condition for 1 bag and num bags == num candies case
            dpTbl[(candyCnt & 0x1)][1] = 1;
            if (candyCnt <= k) {
                dpTbl[(candyCnt & 0x1)][candyCnt] = 1;
            }
            
            for (int nBags = 2; nBags <= min(k, candyCnt); ++nBags) {
                dpTbl[(candyCnt & 0x1)][nBags] =
                    dpTbl[((candyCnt - 1) & 0x1)][nBags - 1] + 
                    (nBags * dpTbl[((candyCnt - 1) & 0x1)][nBags]);
                dpTbl[(candyCnt & 0x1)][nBags] %= moduloFactor;
            }
        }
        return dpTbl[n & 0x1][k];
    }
};
