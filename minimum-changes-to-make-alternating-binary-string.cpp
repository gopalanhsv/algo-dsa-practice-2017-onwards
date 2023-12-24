// n => s.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    minOperations(string s) {
        // Only 2 options to make alternating string from current string
        // 1. Start char 1 => each even index will have 1 and odd index 0
        // 2. Start char 0 => each even index witll have 0 and odd index 1
        auto nOpsForAltStrWith1 = 0;
        auto nOpsForAltStrWith0 = 0;
        // Iterate over string chars sequentially from L->R
        for (auto i = 0; i != s.size(); ++i) {
            // Track the number of ops required to convert current string
            // to an alternating string starting with either 1 or 0
            auto c = s[i]; // Current char
            if (0 == (i & 0x1)) {
                // Even index
                // Alt string starting with 1 (char should be 1)
                nOpsForAltStrWith1 += int('1' - c);
                // Alt string starting with 0 (char should be 0)
                nOpsForAltStrWith0 += int(c - '0');
            } else {
                // Odd index
                // Alt string starting with 1 (char should be 0)
                nOpsForAltStrWith1 += int(c - '0');
                // Alt string starting with 0 (char should be 1)
                nOpsForAltStrWith0 += int('1' - c);
            }
        }

        return min(nOpsForAltStrWith1, nOpsForAltStrWith0);
    }
};
