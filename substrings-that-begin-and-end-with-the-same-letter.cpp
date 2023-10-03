// Time complexity : O(s.size())
// Space complexity : O(26)/O(1)

class Solution {
public:
    long long
    numberOfSubstrings(string s) {
        
        // A char s[i] at a location 'i' in the strings terminates all substrings which
        // commence with each of the prior occurrences of s[i] in the range [0, i - 1)
        // and also the single char substring which commences at 'i'
        // => char s[i] terminates all substrings which start with char s[i] in range [0, i]
        // => Number of substrings which begin and end with any char s[i] would be 
        // the number of occurences of s[i] in the range [0, i]
        
        long long nSubStrs = 0;
        // Hash table tracking the number of occurences of each char till any point in string
        vector<int> charFreqCntTbl('a' + 26, 0);
        // Iterate over the string from L->R sequentially
        for (auto & c : s) {
            // Update the frequency count/number of occurences of current char 'c'
            // from beginning of substring till the current char/index
            charFreqCntTbl[c]++;
            // Current occurence of char 'c' forms a new substring will each and every
            // occurence of 'c' from beginning of string upto/till the current char
            nSubStrs += charFreqCntTbl[c];
        }
        
        return nSubStrs;
    }
};
