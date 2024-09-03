// n => s.size()
// Time Complexity : O(nk)
// Space Complexity : O(1)

class Solution {
public:
    int
    getLucky(string s, int k) {
        
        int sum = 0;
        // Iterate over each char and convert it into equivalent alphabet position
        // Also apply the first transformation (i.e sum of all digits)
        for (auto c : s) {
            // Alphabet position
            int charToNum = c - 'a' + 1;
            // First transformation (takes care of all letters with alphabet
            // positions )
            sum += (charToNum / 10) + (charToNum % 10);
        }
        
        --k;
        // Do the remaining transformations
        while ((k-- > 0) && (sum > 0)) {
            int dSum = 0;
            // Find digit sum of preceeding sum
            while (sum > 0) {
                dSum += sum % 10;
                sum = sum / 10;
            }
            // Update sum
            sum = dSum;
        }
        
        return sum;
    }
};
