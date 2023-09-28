// Time complexity : O(s.size())
// Space complexity : O(s.size())

class Solution {
public:
    string
    maximumOddBinaryNumber(string s) {
        // Problem reduces to given a fixed number of 1-bits and a fixed bit length, 
        // what is the maximum valued odd binary number possible
        // For max-valued binary number, collect all the 1-bits as near to leading/MSB position
        // Since the number is odd, the LSB bit/trailing bit should be 1
        // => Move all 1-bits except a sole one(to be placed at LSB) to be as near the MSB possible

        // Count the number of 1-bits
        auto nSetBits = 0;
        for (auto & c : s) {
            nSetBits += int(c - '0');
        }
        
        auto strSz = s.size();
        if (strSz == nSetBits) {
            // No rebuild required/possible as all bits are set in 's' and would be max odd number
            return s;
        }
        
        // Rebuild the string
        string newStr(strSz, '0');
        // 1-set bit at LSB
        newStr[s.size() - 1] = '1';
        --nSetBits;
        // Remaining number of leading bits to set 1
        for (auto i = 0; nSetBits > 0; --nSetBits, ++i) {
            newStr[i] = '1';   
        }
        return newStr;
    }
};
