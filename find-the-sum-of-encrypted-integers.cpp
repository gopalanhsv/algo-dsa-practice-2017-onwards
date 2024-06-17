// n => nums.size();
// M => average number of digits across all 'nums' elements
// Time complexity : O(nlogM)
// Space complexity : O(1)

class Solution {
public:
    int
    sumOfEncryptedInt(vector<int>& nums) {
        int encSum = 0;
        // Iterate over each number
        for (auto num : nums) {
            // Determine the max digit and number of digits in current number
            int nDigits = 0;
            int maxDigit = 0;
            while (num) {
                auto currDigit = num % 10;
                maxDigit = max(currDigit, maxDigit);
                ++nDigits;
                num /= 10;
            }
            // Encrypt current number
            int encNum = 0;
            for (auto i = 0; i < nDigits; ++i) {
                encNum = (10 * encNum) + maxDigit;
            }
            // Update sum of encrypted numbers
            encSum += encNum;
        }
        
        return encSum;
    }
};
