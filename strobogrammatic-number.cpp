class Solution {
public:
    bool
    isStrobogrammatic(string num) {
        // Set of strobogrammatic digits mapped to respective rotated digit
        unordered_map<char, char> strobDigitTbl(
            {
                {'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}
            });
        
        int nDigits = num.size();
        // To rotate a number by 180 degrees, Reverse the number string
        // Make each digit upside down using above mapping table
        // So one needs to compare each digit with its corresponding
        // upside down counter part of reversed digit and see if they are
        // equal
        
        // Iterate through each digit of number
        for (int i = 0; i != nDigits/ 2 + 1; ++i) {
            // Current digit
            auto & d = num[i];
            // Reversed digit of current
            auto & rd = num[nDigits - 1 - i];
            // Attempt to make current digit upside down.
            // If no valid upside down digit exists or the upside down digit
            // doen't match reversed digit of current digit, the number is not a strob
            auto iter = strobDigitTbl.find(d);
            if (iter == strobDigitTbl.end() || iter->second != rd) {
                return false;
            }
        }

        // All digits of reversed number are identical upside down
        return true;
    }
};
