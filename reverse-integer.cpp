class Solution {
public:
    int
    reverse(int x) {
        if (x == numeric_limits<int>::min()) {
            // Stunt pulled to prevent overflows on changing sign
            // (i.e. -ve number becoming
            return 0;
        }
        
        // Remove sign of the number
        int n = (x < 0) ? -x : x;
        // Extract each digit of number from least significant digit
        // to most significant digit; and move it toward
        long int reverseOfNumber = 0;
        while (n) {
            reverseOfNumber = (10 * reverseOfNumber) + (n % 10);
            
            // Check for overflow
            if (reverseOfNumber > numeric_limits<int>::max() || 
                reverseOfNumber < numeric_limits<int>::min()) {
                return 0;
            }
            
            n /= 10;
        }
        
        // Add the sign back
        return (x < 0) ? -reverseOfNumber : reverseOfNumber;
        
    }
};
