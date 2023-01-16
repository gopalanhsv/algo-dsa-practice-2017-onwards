class Solution {
public:
    int
    newInteger(int n) {
        // The numbers generated with the any number containing digit '9' removed
        // would be as follows:-
        // 1, 2, 3, 4, 5, 6, 7, 8
        // 10, 11, 12, 13, 14, 15, 16, 17, 18
        // 20, 21, 22, 23, 24, 25, 26, 27, 28
        //  --------------------------------
        // 80, 81, 82, 83, 84, 85, 86, 87, 88
        // 100, 101, 102, 103, 104, 105, 106, 107, 108
        // 110, 111, 112, 113, 114, 115, 116, 117, 118
        //  --------------------------------
        // 180, 181, 182, 183, 184, 185, 186, 187, 188
        // 200, 201, 202, 203, 204, 205, 206, 207, 208...and so on
        
        // The above represents successive numbers being generated in the base-9
        // system. The 'n'th number in the system would be the base-9 equivalent of
        // the decimal system 'n'th number
        
        // Convert 'n'th number in base-10 to base-9
        long base9Num = 0;
        long digitTensExponent = 1;
        // Generate base-9 digit from the least significant digit to the
        // most significant digit
        while (n > 0) {
            // Generate base-9 digit for current digit position
            auto base9Digit = n % 9;
            // Update number to account for removal of above digit
            n /= 9;
            
            // Output has to be in decimal format; so put the digit
            // with appropriate power of 10's (from least significant
            // digit position to most significant digit position) 
            base9Num += (base9Digit * digitTensExponent);
            // Update power of 10 multiplicand for the next significant
            // position in the output
            digitTensExponent *= 10;
        }
        
        return base9Num;
    }
};
