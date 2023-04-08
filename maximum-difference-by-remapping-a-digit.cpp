// Time complexity : O(num digits in num) i.e O(log(num))
// Space complexity : O(num digits in num) i.e O(log(num)) 

class Solution {
public:
    int
    minMaxDifference(int num) {
        // Convert number to its equivalent string
        string numStr(to_string(num));
        
        // Adopt greedy approach of remapping all instances of
        // the most significant non-9 digit to 9, in order to get 
        // max possible value of the given number post remap
        
        // Adopt greedy approach of remapping all instances of
        // the most significant non-0 digit to 0, in order to get 
        // min possible value of the given number post remap
        
        // Iterate over the digits of the number from the
        // MSD to the LSD. Determine the most significant
        // non-9 and non-0 digit (they are initialized s.t that
        // the initial value double up as flags to indicate whether
        // they have been found or not)
        char mostSignificantNon0Digit = '0';
        int minVal = 0;
        char mostSignificantNon9Digit = '9';
        int maxVal = 0;
        for (auto & c : numStr) {
            if ((mostSignificantNon0Digit == '0') && (c != '0')) {
                // 'c' is the most significant non-0 digit
                mostSignificantNon0Digit = c;
            }
            if ((mostSignificantNon9Digit == '9') && (c != '9')) {
                // 'c' is the most significant non-9 digit
                mostSignificantNon9Digit = c;
            }

            // Instances of most significant non-0 digit converted to 0
            // for minimum value calc; other digits left as such
            minVal = minVal * 10;
            if (c != mostSignificantNon0Digit) {
                minVal += int(c - '0');
            }
            
            // Instances of most significant non-9 digit converted to 9
            // for minimum value calc; other digits left as such
            maxVal = maxVal * 10;
            if (c == mostSignificantNon9Digit) {
                maxVal += 9;
            } else {
                maxVal += int(c - '0');
            }
        }
        
        return maxVal - minVal;
    }
};
