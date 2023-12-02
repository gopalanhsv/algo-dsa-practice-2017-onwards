// Time complexity : nlogn
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    getNoZeroIntegers(int n) {
        // n should be split into two +ve integers which
        // do not have a zero
        // n is split into a and b s.t n = a + b
        // a is the set of all numbers in range [1, n / 2]
        // b is the set of all numbers in range [n / 2, n - 1]
        for (auto a = 1; a <= n / 2 ; ++a) {
            auto b = n - a;
            if (!isZeroInteger(a) && !isZeroInteger(b)) {
                // a + b = n and a & b are both non-zero integers
                return {a, b};
            }
        }
        // No non-zero integers found for split
        return {};
    }
    
private:
    
    inline bool
    isZeroInteger(int i) {
        // Split 'i' into its digits. If all digits are non-zero return true,
        // false otherwise
        while (i) {
            auto d = i % 10;
            if (0 == d) {
                return true;
            }
            i /= 10;
        }
        return false;
    }
};
