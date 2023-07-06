// Time complexity : O(log n)
// Space complexity : O(log n)
class Solution {
public:
    bool
    isFascinating(int n) {
        if (0 == n) {
            return false;    
        }
        
        // Concatenate number 'n' with '2n' & '3n' and convert to string
        string numStr(to_string(n) + to_string(2 * n) + to_string(3 * n));
        // Hash table tracking seen digits
        unordered_set<char> seenDigitsTbl;
        // Iterate over converted number digits in sequence
        for (auto d : numStr) {
            if ('0' == d) {
                // Presence of 0 => non fascinating
                return false;
            }
            
            if (seenDigitsTbl.end() != seenDigitsTbl.find(d)) {
                // Multiple presence of 'd' digit => non fascinating
                return false;
            }
            seenDigitsTbl.insert(d);
        }
        
        return true;
    }
};
