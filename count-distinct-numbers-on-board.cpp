// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    int
    distinctIntegers(int n) {
        // For any n > 2,
        // Day 1. 'n' placed on the board, n % (n - 1) is 1 => (n - 1) gets placed
        // Day 2. 'n - 1' placed on the board, (n - 1) % (n - 2) is 1 => (n - 2) gets placed
        // Day 3. 'n - 2' placed on the board, (n - 2) % (n - 3) is 1 => (n - 3) gets placed
        // Day 4. 'n - 3' placed on the board, (n - 3) % (n - 4) is 1 => (n - 4) gets placed
        // .............................................................................
        // .............................................................................
        // Finally, '3'   placed on the board, 3 % 2 is 1 => 2 gets placed
        // Cannot do the above with '2', as 2 % 1 is 0.
        // With 10^9 days, all numbers from 2, 3, 4, ..., n - 1, n get placed on board
        // That is , n - 1 - 2 + 1 = n - 1 numbers for n > 2
        
        // For n == 2, cannot find 'x' s.t. 2 % x is '1'. So 2 stays placed on the board
        // For n == 1, cannot find 'x' s.t. 1 % x is '1'. So 1 stays placed on the board 
        // That is, 1 number (the original 'n' 1 or 2) gets placed on board for 'n' as 1/2
        
        return max(n - 1, 1);
    }
};
