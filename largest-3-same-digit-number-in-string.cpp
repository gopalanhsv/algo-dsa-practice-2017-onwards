// n => num.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    string
    largestGoodInteger(string num) {
        // Tracks the value of the digit forming current good integer
        auto goodDigit = 0;
        // Tracks the max valued good digit seen so far
        auto maxGoodDigit = -1;
        // Tracks the length of the contiguous sequence to which
        // the current char in string belongs
        auto currSeqLen = 1;

        // Iterate over the string sequentially from L->R
        for (auto i = 1; i != num.size(); ++i) {
            if (num[i] == num[i - 1]) {
                // Current number extends consecutive sequence having the previous number
                ++currSeqLen;
                if (currSeqLen >= 3) {
                    // Integer forming the current sequence is good
                    goodDigit = num[i] - '0';
                    maxGoodDigit = max(maxGoodDigit, goodDigit);
                }
            } else {
                // Commence new conseuctive sequence at current number
                currSeqLen = 1;
            }
        }
        
        return (-1 != maxGoodDigit) ? string(3, maxGoodDigit + '0') : "";
    }
};
