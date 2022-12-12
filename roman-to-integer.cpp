class Solution {
public:
    int
    romanToInt(string s) {
        if (s.empty()) {
            return 0;
        }
        
        return romanToIntRightToLeftApproach(s);
        //return romanToIntLeftToRightApproach(s);
    }
    
private:
    
    int
    romanToIntRightToLeftApproach(string& s) {
        // Hash table mapping roman symbols to corresponding decimal values
        unordered_map<char, int> romanToIntTbl = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}  
        };

        // Roman numerals are usually ordered from left to right with the largest to the
        // smallest with all numerals being additive, except for certain special cases
        // where reverse ordering applies with smaller numeral getting subtracted from
        // larger one. This observation leads to the following technique:
        // Traverse the roman numeral from right to left
        // A numeral of higher value than the previous one has an additive contribution
        // A numeral of lower value than the previous one has a subtractive contribution
        int rn = 0;
        int prevNumeral = 0;
        for (int i = s.size() - 1; i >= 0; --i) {
            auto currNumeral = romanToIntTbl[s[i]];
            if (currNumeral >= prevNumeral) {
                rn += currNumeral;
            } else {
                rn -= currNumeral;
            }
            prevNumeral = currNumeral;
        }
        return rn;
    }
    
    int
    romanToIntLeftToRightApproach(string& s) {
        // Hash table mapping roman symbols to corresponding decimal values
        unordered_map<char, int> romanToIntTbl = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}  
        };
        // Hash table mapping special case roman numerals to corresponding decimal values
        unordered_map<string, int> specialRomanToIntTbl = {
            {"IV", 4}, {"IX", 9}, {"XL", 40}, {"XC", 90}, {"CD", 400}, {"CM", 900}  
        };
        unordered_map<string, int>::iterator splCaseEndIter = specialRomanToIntTbl.end();
        
        int rn = 0;
        // Traverse the roman string from L -> R
        for (int i = 0; i != s.size(); ++i) {
            // Handle special case first
            if (i <= s.size() - 2) {
                // Roman numeral at current location
                // and the next is a special case instance
                auto splCaseIter = specialRomanToIntTbl.find(s.substr(i, 2));
                if (splCaseIter != splCaseEndIter) {
                    rn += splCaseIter->second;
                    // Need to jump an extra character as two
                    // characters have been processed in one shot
                    ++i;
                    continue;
                }
            }
            rn += romanToIntTbl[s[i]];
        }
        
        return rn;
    }
};
