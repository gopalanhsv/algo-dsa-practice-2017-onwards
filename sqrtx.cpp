class Solution {
public:
    
    int
    mySqrt(int x) {
    
        // x = 0/1
        if (x <= 1) {
            return x;
        }
        
        // Problem reduces to finding largest number 'm' s.t m * m <= x;
        // This can be done by using binary search to explore elements
        // in range [1, x]
        
        int l = 1, r = x;
        int sqrt; // Will act as mid for bin search
        while (l <= r) {
            
            // Compute mid and its square (Doing long long to 
            // avoid runtime overflow on square calculation)
            long long sqrt = l + (r - l) / 2;
            long long squared = sqrt * sqrt;
            
            if (squared == x) {
                return sqrt;
            } else if (squared > (long long)x) {
                r = sqrt - 1;
            } else {
                l = sqrt + 1;
            }
        }
        
        // Search terminates at l > r. Since in earlier iteration,
        // r is max val such that r ^ 2 < x, return r
        return r;
    }
};
