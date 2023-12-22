// n => s.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    maxScore(string s) {
    
        auto strSz = s.size();

        if (0 == strSz) {
            // Error : Empty string
            return 0;
        }

        if (s.size() == 1) {
            // Base case of single char string
            return s[0];
        }
        
        auto nOnesInStr = 0;
        for (auto & x : s) {
            nOnesInStr += int(x - '0');
        }
        
        auto maxScore = 0;
        // Iterate through the string chars sequentially.
        auto nOnesInLeftSubstr = 0;
        for (auto i = 0; i < strSz - 1; ++i) {
            // Split the string into 2 parts at current location, That is,
            // all chars in range [0, i] form left substring; all chars
            // in range [i + 1, strSz - 1] form the right substring
            nOnesInLeftSubstr += int(s[i] - '0') ;
            auto nZerosInLeftSubstr = i + 1 - nOnesInLeftSubstr;
            auto nOnesInRightSubstr = nOnesInStr - nOnesInLeftSubstr;
            // Compute score at this point and update max score
            maxScore = 
                max(maxScore, nZerosInLeftSubstr + nOnesInRightSubstr);
        }
        return maxScore;
    }
};
