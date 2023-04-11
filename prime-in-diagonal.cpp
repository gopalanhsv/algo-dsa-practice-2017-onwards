// Time complexity : O(num rows x sqrt(max number in matrix))
// Space complexity : O(1)

class Solution {
public:
    int
    diagonalPrime(vector<vector<int>>& nums) {
    
        // Num rows, cols
        int n = nums.size();
        
        // Max val of diagonal prime initialized to 'not present i.e. 0'
        int maxDiagPrimeVal = 0;
        
        // Iterate over each of the matrix rows
        for (int r = 0; r != n; ++r) {
            // Check the prime status of forward and reverse diagonal
            // element for the current row
            if (isPrimeNumber(nums[r][r])) {
                // Forward diagonal element is a prime
                maxDiagPrimeVal = max(maxDiagPrimeVal, nums[r][r]);
            }
            if (isPrimeNumber(nums[r][n - 1 - r])) {
                // Reverse diagonal element is a prime
                maxDiagPrimeVal = max(maxDiagPrimeVal, nums[r][n - 1 - r]);
            }
        }
        
        return maxDiagPrimeVal;
    }
    
private:
    
    inline bool
    isPrimeNumber(int n) {
        if (n == 1) {
            return false;
        }
        
        if (n <= 3) {
            // Base case of number 2, 3 => prime number
            return  true;
        }
        
        bool isPrime = true;
        // Attempt to divide the number 'n' using the
        // integers in the range [2, sqrt(n)]
        long i = 2;
        while ((long)i * i <= n) {
            
            if (0 == n % i) {
                // 'i' divides 'n' => 'n' is not a prime
                return false;
            }
            
            // Advance to the next integer
            ++i;
        }
        
        // 'n' is a prime
        return true;
    }
};
