class Solution {
public:
    string
    gcdOfStrings(string str1, string str2) {
        // The two string will have a GCD iff str1 + str2 equals str2 + str1
        // Say GCD of 2 strings is G. Then str1 = mG, str2 = nG (m & n are +ve ints)
        // Then str1 + str2 = (m + n)G = (n + m)G = str2 + str1
        if (str1 + str2 != str2 + str1) {
            // No GCD possible
            return string();
        }
        
        // GCD of the 2 strings will be the prefix of 2 strings with
        // length equal to the GCD of the 2 string lengths
        return str1.substr(0, gcd(str1.size(), str2.size()));
    }
};
