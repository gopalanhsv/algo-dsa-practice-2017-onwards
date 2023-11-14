// n => s.size()
// Time complexity : O(n)
// Space complexity : O(26) / O(1)
class Solution {
public:
    int
    countPalindromicSubsequence(string s) {
        
        // Unique palindromes of length 3 commencing with a char c only be of the 
        // form "c?c", where 'c' & '?' can be any lowercase char
        // i.e. aaa, aba, aca, ..., aya, aza, bab, bbb, bcb, ...and so on        

        // All such palindromes can be formed using first & last occurences
        // of char 'c' in the string for the 1st and 3 char of palindrome; 
        // with the middle char being any one of the unique chars which lie
        // in the substring between the first and last occurence of 'c'
        
        auto strSz = s.size();
        vector<int> lastPosV(26, -1);
        vector<int> firstPosV(26, strSz);
        // Interate over the string from L->R and build the above 2 tables
        for (auto i = 0; i != strSz; ++i) {
            auto & c = s[i];
            firstPosV[c - 'a'] = min(firstPosV[c - 'a'], i);
            lastPosV[c - 'a'] = i;
        }

        int nTotalUniquePalindromes = 0;        
        // Iterate over all possible start chars of 3 letter unique palindromes
        for (auto c = 'a'; c <= 'z'; ++c) {
            // Determine the number of unique 3 letter palindromes
            // starting and ending with char 'c'
            auto firstPosIdx = firstPosV[c - 'a'];
            auto lastPosIdx = lastPosV[c - 'a'];
            
            if (firstPosIdx < lastPosIdx) {
                // Detrmine count of unique chars in the substring
                // s[firstPosIdx + 1, lastPosIdx - 1]
                // Unique char would form the mid char of palindrome
                
                vector<bool> uniqueCharsSeenTbl(26, false);
                auto nUniqueMidChars = 0;
                for (auto i = firstPosIdx + 1; i < lastPosIdx; ++i) {
                    if (!uniqueCharsSeenTbl[s[i] - 'a']) {
                        uniqueCharsSeenTbl[s[i] - 'a'] = true;
                        ++nUniqueMidChars;
                    }
                }
                // Update the total number of unique palindromes
                nTotalUniquePalindromes += nUniqueMidChars;
            }
        }

        return nTotalUniquePalindromes;
    }
};
