// d => log(high) [i.e. num digits in high]
// Time complexity : O(d x (high - low)) 
// Space complexity : O(d)
class Solution {
public:
    int
    countSymmetricIntegers(int low, int high) {
        auto nSymmetric = 0;
        // Iterate over each integer in the specified range
        for (int n = low; n <= high; ++n) {
            // Convert current integer to equivalent string
            string numStr(to_string(n));
            int nStrSz = numStr.size();
            // Use 2 pointer technique to check if current integer is symmetric
            if (0 == (nStrSz & 0x1)) {
                auto l = 0;
                auto r = nStrSz - 1;
                int loSum = 0;
                int hiSum = 0;
                while (l < r) {
                    hiSum += int(numStr[l] - '0');
                    loSum += int(numStr[r] - '0');
                    ++l, --r;
                }
                
                if (loSum == hiSum) {
                    ++nSymmetric;
                }
            }
        }
        
        return nSymmetric;
    }
};
