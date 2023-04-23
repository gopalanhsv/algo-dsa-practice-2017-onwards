// Time complexity : O(s.size())
// Space complexity : O(1)

class Solution {
public:
    int
    numDecodings(string s) {
        if (s.empty() || s[0] == '0') {
            // Base case of empty string/string starting with '0' -- no decoding
            return 0;
        }
        
        // String of size 1 not starting with '0'
        int strSz = s.size();
        if (strSz == 1) {
            return 1;
        }
        
        // String of size 2 or more (not starting with 0)


        // Number of ways to decode the substring ending
        // at position 'i - 1' (one char back)
        long long nWays_i_1 = 1;
        // Number of ways to decode the substring ending
        // at position 'i - 1' (two chars back)
        long long nWays_i_2 = 1;
        // Number of ways to decode the substring ending
        // at current position 'i'
        long long nWays_i = 0;
        // Commence from the 2nd position in decoded message. Iterate over the chars
        // sequentially and compute the number of ways in which message upto current
        // position can be decoded
        for (int i = 1; i != strSz; ++i) {
            // Compute number of ways to decode the subtring
            // ending at current position 'i' i.e. s[0, i]
            nWays_i = 0;
            auto & currChar = s[i];
            if (currChar != '0') {
                // Single digit string ending at current location 'i' is a valid
                // encoded message. It forms a valid message with each of the
                // valid encoded messages ending one chars back (i.e messages
                // formed by the substring s[0, i - 1])
                nWays_i = nWays_i_1;
            }
            
            // Check if the two digit string ending at the current index 'i'
            // forms a valid two digit encoded message. It should be a valid two
            // digit number in the closed range [10, 26]
            auto & prevChar = s[i - 1];
            int twoDigitNum = (prevChar - '0') * 10 + (currChar - '0');
            if (twoDigitNum >= 10 && twoDigitNum <= 26) {
                // Two digit string ending at current location 'i' is a valid
                // encoded message. It forms a valid message with each of the
                // valid encoded messages ending two chars back (i.e messages
                // formed by the substring s[0, i - 2])
                nWays_i += nWays_i_2;
            }

            nWays_i_2 = nWays_i_1;
            nWays_i_1 = nWays_i;
        }
        
        return nWays_i;
    }
}; 
