// Time complexity : O(n ^ 2)
// Space complexity : O(n)

class Solution {
public:
    int
    integerBreak(int n) {
        if (n <= 1) {
            // Base case : n <= 1 can be expressed only as 0 x 0/ 0 x 1
            return 0;
        }    
        
        // Number 'n' can be split as series of 'k' +ve integers s.t. k >= 2
        // If F(x) = max product obtained by splitting 'x' into at least 2+ve integers;
        // and 'x' is expressed as x = x1 + x2 where both x1/x2 >= 0; then we have -
        // F(x) = max(x1 * x2, x1 * F(x2), F(x1) * x2, F(x1) * F(x2)) for all 
        // possible values of x1/x2 satisfying x = x1 + x2, with x1 & x2 >= 1
        // The factor combinations of F(x1)/F(x2) take care of the issue of
        // further splitting x1/x2
        
        // Build up the values of F(x) for 1, 2, 3, ..., x using solutions to 
        // smaller/earlier subproblems x1/x2 where x = x1 & x2 in order to compute F(x)
        // => DP approach
        
        // maxProdTbl[x] is the max product obtainable for integer 'x'
        vector<long> maxProdTbl(n + 1, 1);
        // Init to '1' and not '0' otherwise products built using these will cancel out
        maxProdTbl[0] = maxProdTbl[1] = 1;
        
        // Iterate over each number from 2 to 'n' sequentially
        for (int num = 2; num <= n; ++num) {
            // Compute the max product possible via integer break for number 'num'
            long maxProd = 1;
            // Build all possible complementary sum combinations (n1, n2) for 'num'; s.t. num = n1 + n2
            // Need to do only till nums/2 as the combinations (n1, n2) would be symmetric
            for (long n1 = 1; n1 <= num / 2; ++n1) {
                long n2 = num - n1;
                // Compute the max possible product for 'num' with current split sum (n1, n2)
                // and update the max product for 'num' seen so far
                maxProd = max(maxProd, maxProdTbl[n1] * maxProdTbl[n2]);
                maxProd = max(maxProd, maxProdTbl[n1] * n2);
                maxProd = max(maxProd, n1 * maxProdTbl[n2]);
                maxProd = max(maxProd, n1 * n2);
            }
            // Update the max product for 'num' in cache
            maxProdTbl[num] = maxProd;
        }
        
        return maxProdTbl[n];
    }
};
