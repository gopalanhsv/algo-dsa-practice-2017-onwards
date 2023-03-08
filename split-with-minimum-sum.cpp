class Solution {
public:
    int
    splitNum(int num) {
        // From a given set a digits, smallest possible number is formed via the greedy
        // approach of always selecting the least digit available from the set while
        // building the new number from left to right. This ensures that always the more
        // significant digits of new numbers have lesser magnitude (leading to a lesser
        // overall value for the entire new number) compared to the lower significant digits
        
        // Generalizing the above approach to form 2 new numbers with smallest possible 
        // values from a given set of digits, build the 2 new numbers by selecting the
        // smallest digit available with pool and using it to populate the new number
        // digits from left to right in round robin - i.e. new number 1, then new number 2,
        // then new number 1 again and so on
        
        // Splitting original number into two new numbers having smallest sum =>
        // Splitting original number into two new numbers having smallest magnitude each
        
        // Arrange the digits of original number in ascending order
        string numStr = to_string(num);
        sort(numStr.begin(), numStr.end());
        
        // Build the two new numbers of smallest magnitude
        int newNum1 = 0;
        int newNum2 = 0;
        int nDigits = numStr.size();
        // Iterate over the available digits from smallest to largest
        for (int i = 0; i < nDigits; ++i) {
            auto digit = numStr[i] - '0';
            newNum1 = 10 * newNum1 + digit;
            if (++i < nDigits) {
                digit = numStr[i] - '0';
                newNum2 = 10 * newNum2 + digit;
            }
        }
        
        return newNum1 + newNum2;
    }
};
