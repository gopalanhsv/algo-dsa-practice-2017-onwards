// n => nums.size()
// m => max value in nums
// Time complexity : O(nlogm)
// Space complexity : O(1)
class Solution {
public:
    int
    countBeautifulPairs(vector<int>& nums) {
        
        int nPairs = 0;
        // Hash table tracking occurence count of first digits
        // in the numbers seen so far
        vector<int> seenFirstDigitCnt(10, 0);
        // Iterate over elements sequentially from L->R
        for (auto num : nums) {
            // Last digit for current num
            auto lastDigit = num % 10;
            // Iterate over all possible first digits
            for (auto d = 1; d <= 9; ++d) {
                if (1 == gcd(d, lastDigit)) {
                    // All numbers seen prior to current number having 'd' as
                    // first digit form beautiful pairs with current number 'num'
                    auto nCoprimes = seenFirstDigitCnt[d];
                    nPairs += nCoprimes;
                }
            }
            // First digit of current number
            while (num >= 10) {
                num /= 10;
            }
            // Update occurence count of first digits in nos seen so far
            seenFirstDigitCnt[num]++;
        }
        
        return nPairs;
    }
};
