// Time complexity : O(((high - low) / k ) x (num digits in max number)) => O((high - low) / k)
// Space complexity : O(1)
class Solution {
public:
    int numberOfBeautifulIntegers(int low, int high, int k) {

        // Since beautiful number should have same number of even and odd digits,
        // number of digits in the beautiful number must be even => the beautiful
        // number must lie in one of the following ranges:-
        // (1) 10 - 99
        // (2) 1000 - 9999
        // (3) 100000 - 999999
        // (4) 10000000 - 99999999
        // (5) 1000000000 - 1000000000 (since num < 10^9)
        
        // Also beautiful number should be a multiple of 'k' & lie in range [low, high]
        auto nBeautiful = 0;
        nBeautiful += countBeautifulInRange(max(low, 10), min(99, high), k);
        nBeautiful += countBeautifulInRange(max(low, 1000), min(9999, high), k);
        nBeautiful += countBeautifulInRange(max(low, 100000), min(999999, high), k);
        nBeautiful += countBeautifulInRange(max(low, 10000000), min(99999999, high), k);
        nBeautiful += countBeautifulInRange(max(low, 1000000000), min(1000000000, high), k);
        return nBeautiful;
    }
    
private:
    
    int
    countBeautifulInRange(int low, int high, int k) {        
        // Beautiful number should be a multiple of 'k' & lie in range [low, high]
        // Determine nearest multiple of 'k' g.e. 'low'
        // Determine nearest multiple of 'k' l.e. 'high'
        int loMultiple = k * ceil(double(low) / k);
        int hiMultiple = k * floor(double(high) / k);
        auto nBeautiful = 0;
        // Iterate over each candidate multiple of 'k' in range [loMultiple, hiMultiple]
        // and check if it is beautiful
        for (long candidateNum = loMultiple; 
             candidateNum <= hiMultiple; candidateNum += k) {
            long cn = candidateNum;
            // Check if candidate has equal number of odd & even digits
            auto evenDigitCnt = 0;
            auto oddDigitCnt = 0;       
            while (cn > 0) {
                auto d = cn % 10;
                cn /= 10;
                
                if ((d & 0x1) == 1) {
                    ++oddDigitCnt;
                } else {
                    ++evenDigitCnt;
                }
            }
            if (oddDigitCnt == evenDigitCnt) {
                ++nBeautiful;
            }
        }
        
        return nBeautiful;
    }
};
