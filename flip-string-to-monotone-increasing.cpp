class Solution {
public:
    int
    minFlipsMonoIncr(string s) {
        // Min number of flips required to make the substring [0, i] of the
        // original string monotonically increasing with the last character
        // as either 0 or 1
        int minFlipsWithLastCharAs0 = 0;
        int minFlipsWithLastCharAs1 = 0;
        
        // Start with substring [0, 0]. Compute number of flips reqd to
        // make string monotonically increasing as per last char value
        if (s[0] == '0') {
            // substring[0, 0] last char 1 post flip requires 
            // current character '0' at index '0' to be flipped
            minFlipsWithLastCharAs1 = 1;
        } else {
            // substring[0, 0] last char 0 post flip requires 
            // current character '1' at index '0' to be flipped
            minFlipsWithLastCharAs0 = 1;
        }

        int strSz = s.size();
        
        // Increment the substring [0, i - 1] by one char to right
        // Compute number of flips reqd to make string monotonically
        // increasing as per last char value via DP
        for (int i = 1; i != strSz; ++i) {
    
            int minFlipsWithCurrCharAs0, minFlipsWithCurrCharAs1;
            
            if (s[i] == '1') {
                // Value of string at current location is '1'
                
                // substring[0, i] with s[i] = '0' after flip requires 
                // current character s[i] to be flipped
                // s[i] = '0' requires s[i - 1] to be '0' post flip for
                // monotone increasing substring[0, i]
                minFlipsWithCurrCharAs0 = 1 + minFlipsWithLastCharAs0;
                
                // substring[0, i] with s[i] = '1' after flip requires 
                // current character s[i] not to be flipped
                // s[i] = '1' requires s[i - 1] to be either '0'/'1' post flip for
                // monotone increasing substring[0, i]
                minFlipsWithCurrCharAs1 =
                    min(minFlipsWithLastCharAs0, minFlipsWithLastCharAs1);
            } else {
                // Value of string at current location is '0'
                
                // substring[0, i] with s[i] = '0' after flip requires 
                // current character s[i] not to be flipped
                // s[i] = '0' requires s[i - 1] to be '0' post flip for
                // monotone increasing substring[0, i]
                minFlipsWithCurrCharAs0 = minFlipsWithLastCharAs0;
                
                // substring[0, i] with s[i] = '1' after flip requires 
                // current character s[i] to be flipped
                // s[i] = '1' requires s[i - 1] to be either '0'/'1' post flip for
                // monotone increasing substring[0, i]
                minFlipsWithCurrCharAs1 = 1 +
                    min(minFlipsWithLastCharAs0, minFlipsWithLastCharAs1);
            }
        
            // Update the minimum number of flips required to make substring [0, i]
            // substring monotone increasing with last char 0, 1 respectively
            minFlipsWithLastCharAs0 = minFlipsWithCurrCharAs0;
            minFlipsWithLastCharAs1 = minFlipsWithCurrCharAs1;
        }
        
        // Returning the min number of flips required to make substring[0, n - 1]
        // monotone increasing (choose last char as 0 or 1, whichever requires min flips)
        return min(minFlipsWithLastCharAs0, minFlipsWithLastCharAs1);
    }
};
