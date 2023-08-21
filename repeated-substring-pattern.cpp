// n = s.size()
// Time complexity : O(n)
// Space complexity : O(n)
class Solution {
public:
    bool
    repeatedSubstringPattern(string s) {
        if (s.size() < 2) {
            return false;
        }
        
        // Intuition :- If string is made up of repeated substrings, then doubling
        // the string will result in a string with the same repeated substrings.
        // Dropping first and last character in this new string will result in
        // a string which has the original string
        
        // 'S' is a string which consists only of a repeated substring pattern 'P'
        // Then at least S should be s.t S = P + P
        // => Repeated string of original string R = S + S = P + P + P + P.
        // Dropping first and last chars of R results in R' = Prstart + P + P + Prend
        // where Prstart => P with 1st char removed
        // where Prend => P with last char removed
        // => R' = PrStart + S + Prend
        // => Original string S is found in the double string of S with 1st & last chars dropped

        // Construct a new string by repeating the original string
        string repeatedString = s + s;
        // Drop 1st and last chars from repeated string
        repeatedString = repeatedString.substr(1, repeatedString.size() - 2);
        // Original string made up of repeated patterns only if
        // it occurs in the above processed string
        return repeatedString.find(s, 0) != string::npos;
    }
};
