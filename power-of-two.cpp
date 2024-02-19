// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    bool
    isPowerOfTwo(int n) {
        // Base case
        if (n <= 0) {
            return false;
        }

        // A number which is a power of 2 will only have a sole bit set
        // in its binary representation.
        // => Clear the rightmost set bit via K & R technique. A number
        // which is a power of 2 will become 0
        return (n & (n - 1)) == 0;
    }
};
