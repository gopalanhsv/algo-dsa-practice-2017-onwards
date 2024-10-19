// Time Complexity : O(nlogn)
// Space Complexity : O(1)

class Solution {
public:
    char
    findKthBit(int n, int k) {
        // V(n, b) = value of bth digit (1-indexed from left) of nth binary string
        // and 'm' be the location of middle digit
        // 1) '1' if b == m
        // 2) V(n - 1, b) if b lies in left half of string, i.e. b < m
        // 3) invert(V(n, m - (b - m)) if b lies in right half of string, i.e. b < m
        //  = invert(V(n - 1, m - (b - m))
        
        bool invertDigit = false;
        while (n > 1) {
            // Compute the number of digits in the 'nth' binary string (for current n) 
            long nDigits = numDigits(n);
            // Middle position for current binary string
            long midIdx = nDigits / 2 + 1;
            if (k == midIdx) {
                return (invertDigit) ? '0' : '1'; 
            }
            if (k > midIdx) {
                // Case 3 from above => invert digit and reverse, then decrement 'n'
                invertDigit = !invertDigit;
                k = midIdx - (k - midIdx);
            } else {
                // Case 2 from above => no change, just decrement 'n'
            }
            --n;
        }
        
        // Reached till S1
        return (invertDigit) ? '1' : '0'; 
    }
    
private:
    
    long
    numDigits(int n) {
        if (n == 1) {
            return 1;
        }
        
        long p = 1;
        while (n > 0) {
            p *= 2;
            --n;
        }
        return p - 1;
    }
};
