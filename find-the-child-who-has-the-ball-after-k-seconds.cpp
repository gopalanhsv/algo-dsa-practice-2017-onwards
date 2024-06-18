// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    int
    numberOfChild(int n, int k) {
        // Passing ball from child#0 to child#n-1 takes n - 1 seconds
        // Passing ball in reverse direction from from child#n-1 to child#0 takes n - 1 seconds
        // => One roundtrip from child#0 back to itself takes 2n - 2 seconds
        // Normalize 'k' to account for round trips
        k %= ((n << 1) - 2);
        
        // Now 'k' accounts for at most the last round trip from child#0 
        if (k > n - 1) {
            // 'k' seconds finish on the way back from child#n-1 back to child#0
            k -= (n - 1);
            return n - 1 - k;
        }
        // 'k' seconds finish on the way from child#0 to child#n-1
        return k;
    }
};
