class Solution {
public:
    int
    alternateDigitSum(int n) {
        // Track current running alternate digit sum
        int altSum = 0;
        // Sign to be applied to digit to be added to
        // alternate digit sum
        int sign = 1;
        // Compute the digit sum from the least significant
        // digit to the most significant digit by splitting
        // the number into its digits
        while (n) {
            
            int currDigit = n % 10;
            n /= 10;
            // Update the alternating digit sum by applying
            // sign to current digit
            altSum += (sign * currDigit);
            // Flip the sign in readiness for next digit
            sign = -sign;
        }

        // Update the sign to reflect sign applied to most
        // significant digit (i.e immediate previous digit)
        sign = -sign;
        // Most significant digit should have a +ve sign;
        // adjust sign of the computed sum appropriately
        return (sign < 0) ? -altSum : altSum;
    }
};
