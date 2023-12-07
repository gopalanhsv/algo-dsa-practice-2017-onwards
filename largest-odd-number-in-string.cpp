// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    string
    largestOddNumber(string num) {
        
        // Problem reduces to find the last/rightmost odd digit in the string
        // The entire substring in range [0, rightmost odd digit location]
        // will be the largest valued odd integer
#if 1
        for (int i = num.size() - 1; i >= 0; --i) {
            // Digit equivalent of current char
            auto d = num[i] - '0';
            if (1 == (d & 0x1)) {
                // Current char is an odd digit; so yay largest
                // odd number is substring in closed range [0, i]
                return num.substr(0, i + 1);
            }
        }
        
        // No odd digit in string; hence no odd number
        return string();
#else
        // One line search for last odd number from right
        return num.substr(0, num.find_last_of("13579") + 1);
#endif
    }
};
