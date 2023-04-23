// Time complexity : O(s.size() x logk)
// Space complexity : O(s.size())

class Solution {
public:
    int
    numberOfArrays(string s, int k) {
        int sLen = s.size();
        const int moduloFactor = 1000000000 + 7;
        
        // nArraysTbl[i] is number of arrays which can be restored
        // as per input constraints (all integers in range [1, k] with
        // no leading 0's) using the substring s[i, sLen)
        vector<long> nArraysTbl(sLen, 0);
        
        // The last char in the string forms a single array
        // consisting of single element with value 
        // digit value of the char is in the range [1, k]
        auto lastChrDigit = s[sLen - 1] - '0';
        if ((lastChrDigit > 0) && (lastChrDigit <= k)) {
            nArraysTbl[sLen - 1] = 1;
        }
        
        // Iterate sequentially from the 2nd last char of string to the first char
        for (int i = sLen - 2; i >= 0; --i) {   
        
            // Determine the number of arrays which can be restored as per
            // input constriants using the substring [i, sLen) -- i.e. from
            // current char to string end
            
            if (s[i] == '0') {
                // Current char '0' can be restored as follows:-
                // 1. Add '0' as a separate element to all valid arrays 
                //    generated using s[i + 1, sLen)
                // 2. Add '0' as a leading digit to the leading elements
                //    of all arrays generated using s[i + 1, sLen)
                // Both of the above cases are not allowed during restoration
                continue;
            }
            
            // Current curr s[i, i] is non-'0'. 
            // Substring s[i, sLen] can be restored as follows:-
            // 1. Add s[i, i] as a leading element to all valid arrays 
            //    generated using s[i + 1, sLen)
            // 2. Add s[i, i] as a leading digit to the leading elements
            //    of all arrays generated using s[i + 1, sLen)
            
            long arrayCnt = 0;
            long leadingElemVal = 0;
            
            // Iterate over the indices sequentially from i to sLen to form
            // possible leading elements to be prefixed to valid arrays
            // formed earlier using the remaining part of the substring
            for (int j = i; j < sLen; ++j) {
                
                long currDigit = s[j] - '0';
                // Number representation of leading element formed by
                // substring s[i, j]
                leadingElemVal = leadingElemVal * 10 + currDigit;
                if (leadingElemVal > k) {
                    // Current Leading element value exceeds 'k', so all
                    // possibilities which have leading element beyond s[i, j - 1]
                    // also exceed 'k' and do not satify restoration constraints
                    break;
                }
                
                if (j + 1 < sLen) {
                    // s[i, j] is leading element of each array formed via
                    // substring s[j + 1, sLen)
                    arrayCnt += nArraysTbl[j + 1];
                } else {
                    // s[i, j] OR s[i, sLen) is leading element and sole array element
                    ++arrayCnt;
                }
                arrayCnt %= moduloFactor;
            }
            // Update the number of arrays restored by s[i, sLen)
            nArraysTbl[i] = arrayCnt;
        }
        
        return nArraysTbl[0];
    }
};
