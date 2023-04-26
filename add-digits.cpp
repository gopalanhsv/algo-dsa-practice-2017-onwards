// Time complexity : O(num digits in 'num') => O(log num)
// Space complexity : O(1)

class Solution {
public:
    int addDigits(int num) {
        // Base case for single digit numbers
        if (num < 10) {
            return num;
        }
        
        // Double digit and above numbers. Repeatedly take the
        // sum of digits and break down
        int digitSum = num;
        while (num > 9) {
            int digitSum = 0;
            while (num) {
                digitSum += num % 10;
                num /= 10;
            }
            num = digitSum;
        }
        
        return num;
    }
};
