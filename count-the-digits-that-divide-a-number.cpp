class Solution {
public:
    int
    countDigits(int num) {
        int numCopy = num;
        // Tracks the number of digits dividing the number
        int nDigits = 0;
        // Split the number into its digits (R -> L)
        while (num) {
            int d = num % 10;
            num /= 10;
            if ((0 != d) && (0 == numCopy % d)) {
                // Current digit 'd' divides 'num'
                ++nDigits;
            }
        }
        
        return nDigits;
    }
};
