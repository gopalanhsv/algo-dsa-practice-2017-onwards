class Solution {
public:
    bool
    isPalindrome(int x) {
        // Negative number not a palindrome
        if (x < 0) {
            return false;
        }
        // single digit numbers are palindromes
        if (x < 10) {
            return true;
        } 
        
        // Reverse the number
        long reversedNum = 0;
        int n = x;
        while (n) {
            reversedNum = 10 * reversedNum + (n % 10);
            n /= 10;
        }
        // Compare reversed number with original
        return reversedNum == x;
        
        // Via bit manipulation
        int rn = x;
        int mask = 0x00000000FFFFFFFF;
        rn = (rn & (mask << 16) >> 16) | (rn & mask << 16);
        
        mask = 0x00FF00FF00FF00FF;
        rn = ((rn & (mask << 8)) >> 8) | ((rn & (mask)) << 8);
        
        mask = 0x0F0F0F0F0F0F0F0F;
        rn = ((rn & (mask << 4)) >> 4) | ((rn & mask) << 4); 
        
        mask = 0x0303030303030303;
        rn = ((rn & (mask << 4)) >> 4) | ((rn & mask) << 4); 
        
    }
};
