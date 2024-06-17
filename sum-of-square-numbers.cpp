// Time complexity : O(c)
// Space complexity : O(1)

class Solution {
public:
    bool
    judgeSquareSum(int c) {
        return twoPointerApproach(c);
    }
    
private:
    
    bool
    twoPointerApproach(int c) {
        if (c <= 2) {
            return true;    
        }
        
        // Search for a candidate 'a' & 'b' s.t. a^2 + b^2 = c 
        // => b^2 = c - a^2 
        // => b possible max value of sqrt(c) (when 'a' is 0)
        
        // Use two pointer method to search in the range [0, sqrt(c)] for 'a' and 'b'
        // (since search range is sorted) till sum constraint is satisfied
        // Init two pointers at the ends of the range
        long long a = 0;
        long long b = sqrt(c) + 1;
        long long aSquared = a * a;
        long long bSquared = b * b;
        // Loop till the range shrinks to nil size
        while (a <= b) {

            // Compute tentative sum
            long long candidateSum = aSquared + bSquared;
            if (candidateSum == c) {
                // Integers 'a' & 'b' satisfying given constraint found
                return true;
            } else if (candidateSum > c) {
                // Need to look for a lower sum, decrement 'hi' pointer
                --b;
                bSquared = b * b;
            } else {
                // Need to look for a higher sum, increment 'lo' pointer
                ++a;
                aSquared = a * a;
            }
        }
        
        return false;
    }
};
