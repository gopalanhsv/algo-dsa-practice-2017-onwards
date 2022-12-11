class Solution {
public:
    int
    myAtoi(string s) {
        if (s.empty()) {
            return 0;
        }
        
        typedef string::size_type strSzT;
        strSzT strSz = s.size();
        // Skip leading spaces till a non space char hit
        strSzT i = 0;
        while (i < strSz && isspace(s[i])) {
            ++i;
        }
        
        if (i == strSz) {
            return 0;
        }
        
        // Sign char if any
        int sign = 1;
        if (s[i] == '-') {
            sign = -1, ++i;
        } else if (s[i] == '+') {
            ++i;
        }
        
        // Decode the number
        long int num = 0;
        for (; i < strSz; ++i) {
            //auto & c = s[i];
            if (isdigit(s[i])) {
                num = 10 * num + int(s[i] - '0');
                if (num > numeric_limits<int>::max()) {
                    break;
                }
            } else {
                break;
            }
        }    
        // Apply sign
        if (sign < 0) {
            num = -num;
        }
        
        // Truncate the number if it goes beyond 'int' limits
        if (num > numeric_limits<int>::max()) {
            return numeric_limits<int>::max();
        } else if (num < numeric_limits<int>::min()) {
            return numeric_limits<int>::min();
        }
        return num;
    }
};
