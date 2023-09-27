// n <=> s.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    string
    decodeAtIndex(string s, int k) {
        // Compute the length of decoded string
        unsigned long long decodedLen = 0;
        for (auto & c : s) {
            if (isalpha(c)) {
                ++decodedLen;
            } else {
                decodedLen = decodedLen * (c - '0');
            }
        }
        
        // Key insight here is that if a (sub)string of size 'L' is repeated
        // 'R - 1' after the original substring, the new string length is 'RL'
        // The 'k' th (1-indexed) char in the new string of length 'RL' would
        // be the 'k % L' (1-indexed) char of the original substring of size 'L'
        
        // Work backwards using the length of decoded string to get the
        // exact char at index location 'k' by adjust the value of 'k' to
        // account for repetition of substrings at various decoding stages
        // Iterate over the encoded string from R->L sequqntially 
        unsigned long long decodedSubsStrLen = decodedLen;
        for (auto i = s.size() - 1; i >= 0; --i) {
            auto & c = s[i];
            if (isalpha(c)) {
                // Current char is a letter => it is written directly to output as is
                // and hence takes only 1 char post decoding
                if (0 == k % decodedSubsStrLen) {
                    // s[i + 0] is the 'k' th char of s[0, i]. Since 'k' is adjusted
                    // while working backwards, it is also the 'k' th char of 
                    // entired decoded string
                    return string(1, s[i]);
                } else {
                    // Compute the length of decoded substring s[0, i - 1]
                    // (i.e. exclude decoding chars for current char)
                    --decodedSubsStrLen;
                }
            } else {
                // Current char is a digit
                // => Decoded substring s[0, i - 1] is repeated 's[i]' times
                // Compute the number of times decoded substring s[0, i - 1] is repeated
                auto nRepeats = int(c - '0');
                // Compute the length of decoded substring s[0, i - 1] (prior to repetition)
                // (i.e. exclude decoding chars for current char)
                decodedSubsStrLen /= nRepeats;
                // The 'k' th  (1-idxed) char of original decoded substring s[0, i]
                // formed by repeating substring s[0, i - 1] 'nRepeats' times would
                // the 'k % decoded substring s[0, i - 1] length' th char of s[0, i - 1]
                // Adjust 'k' appropriately to map to smaller substring
                k = k % decodedSubsStrLen;
            }
        }
        
        // Error => string cannot be encoded/decoded as per given rules
        return "Error";
    }
};
