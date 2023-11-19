// Time complexity : O(log num)
// Space complexity : O(log num)
class Solution {
public:
    int
    maximumSwap(int num) {
        // A digit in a higher significant position (i.e. towards left) contributes
        // more to the number magnitude compared to that a lower significant position
        // (towards right)
        
        // Adopt greedy approach of maximizing the digit at higher significant
        // position as follows:-
        // Iterate over the digits of number from higher/left to lower/right
        // At a position i, attempt to swap the digit with a digit of highest value which
        // occurs to the right of 'i'. If swap is possible, we are done (max of one
        // allowable swap)
        
        // Convert number to its string equivalent
        auto numStr = to_string(num);
        int nDigits = numStr.size();
        // maxDigitIdxToRightV[x] is the location of max value digit which occurs in
        // numStr[i + 1, ...] i.e. the max valued digit in lower significant locations
        // compared to 'i'
        vector<int> maxDigitIdxToRightV(nDigits, nDigits - 1);
        int maxDigitIdxToRight = nDigits - 1;
        for (int i = nDigits - 2; i >= 0; --i) {
            auto nextDigitToRight = int(numStr[i + 1] - '0');
            // Location of max digit in to right of index 'i'
            auto maxDigitValToRight = int(numStr[maxDigitIdxToRight] - '0');
            if (nextDigitToRight > maxDigitValToRight) {
                maxDigitIdxToRight = i + 1;
            }
            maxDigitIdxToRightV[i] = maxDigitIdxToRight;
        }

        // Iterate over digits of 'num' from left to right
        for (auto pos = 0; pos < nDigits - 1; ++pos) {
            auto & currDigit = numStr[pos];
            auto & maxDigitToRight = numStr[maxDigitIdxToRightV[pos]];
            if (currDigit < maxDigitToRight) {
                // Swap digit at current position with the max digit to its right
                swap(currDigit, maxDigitToRight);
                break;
            }
        }
        
        return stoi(numStr);
    }
};
