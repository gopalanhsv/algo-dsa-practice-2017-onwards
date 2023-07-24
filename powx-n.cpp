// Iterative approach
// Time complexity : O(log n)
// Space complexity : O(1)

// Recursive approach
// Time complexity : O(log n)
// Space complexity : O(log n)

class Solution {
public:
    double
    myPow(double x, int n) {

        // To take care of overflow issues due to negation
        // This is a very IMP point esply for exp of 2 ^ 31 - 1
        long long exp = n;
        // Adjust x if exponent -ve
        if (exp < 0) {
            exp = -exp;
            x = 1.0 / x;
        }
        
        // Recursively compute the power 
        // return fastPowerRec(x, exp);
        // Iteratively compute the power
        return fastPowerIterative(x, exp);
    }
    
private:
    
    double
    fastPowerRec(double x, long long n) {
        // Base case termination condition
        if (1 == n) {
            return x;
        }
        if (0 == n) {
            return 1;
        }
        
        // Recursively solve the problem for n / 2 
        double res = fastPowerRec(x, n >> 1);
        
        if (n & 1) {
            // Odd exponent
            return res * res * x;
        } else {
            // Even exponent
            return res * res;
        }
    }
    
    double
    fastPowerIterative(double x, long long n) {
    
        double result = 1.0;
        while (n) {
            if (n & 1) {
                // Odd exponent
                // This will get executed also at last iteration as all
                // even and odd exponents reduce to 1 on consecutive halving
                result *= x;
            }
            n = (n >> 1);
            x *= x;
        }
        
        return result;
    }
    
};
