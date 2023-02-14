class Solution {
public:
    string
    addBinary(string a, string b) {
        // Base case of either string being null
        if (a.empty()) {
            return b;
        }
        if (b.empty()) {
            return a;
        }
        
        string sumStr;
        // Iterate over both strings from right to left
        // adding the correponding digits along with carry
        // from previous digit sum together
        char carry = 0;
        int i = a.size() - 1;
        int j = b.size() - 1;
        while (carry != 0 || i >= 0 || j >= 0) {
            char digitSum = carry;
            if (i >= 0) {
                digitSum += (a[i--] - '0');
            }
            if (j >= 0) {
                digitSum += (b[j--] - '0');
            }
            // Base is 2. Append least significant digit of sum to output
            // and most siignificant digit goes to carry
            sumStr += ('0' + (digitSum % 2));
            carry = digitSum / 2;
        }
        
        // Reverse the output sum string
        reverse(sumStr.begin(), sumStr.end());
        return sumStr;
    }
};
