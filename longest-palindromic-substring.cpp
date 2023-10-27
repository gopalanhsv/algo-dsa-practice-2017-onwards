// n => s.size()

// Bottom up DP Approach
// Time complexity : O(n ^ 2)
// Space complexity : O(n ^ 2)

// Centering Approach
// Time complexity : O(n ^ 2)
// Space complexity : O(1)
class Solution {
public:
    string
    longestPalindrome(string s) {
        
        if (s.size() <= 1) {
            // Base case of empty string/single char string
            return s;
        }
        
        //return countSubstringsDP(s);
        return longestPalindromeViaCentering(s);
    }
    
private:
    
    string
    countSubstringsDP(string& s) {
        
        // String size
        int n = s.size();

        // isPalindromeTbl[i][j] is true if the substring s[i, j] is a palindrome, false otherwise
        vector<vector<bool> > isPalindromeTbl(n, vector<bool>(n, false));
        // Mapping from a string to index locations within the string
        // where the character is present
        unordered_map<char, vector<int> > chrToLocationTbl;
        
        // Longest palindrome initialized to first string char
        int longestPalindromLen = 1;
        int longestPalindromeLoIdx = 0;
        
        // Iterate over the string sequentially char by char
        for (int idx = 0; idx != n; ++idx) {
        
            auto & currChar = s[idx];
            
            // Current character by itself forms a single character palindrome
            isPalindromeTbl[idx][idx] = true;
            
            // Check for current character s[idx] terminating palindromes commencing
            // at earlier instances of same char in the substring s[0, idx - 1] 
            auto & chrPrevIndicesV = chrToLocationTbl[currChar];
            // Iterate over earlier instances of current character
            for (auto & prevIdx : chrPrevIndicesV) {
                // A palindrome can end at the current char at 'idx' only if the
                // substring s[prevIdx + 1, idx - 1] is a palindrome/null string
                if (idx - prevIdx == 1) {
                    isPalindromeTbl[prevIdx][idx] = true;
                    auto palindromeLen = idx - prevIdx + 1;
                    if (palindromeLen > longestPalindromLen) {
                        longestPalindromLen = palindromeLen;
                        longestPalindromeLoIdx = prevIdx;
                    }
                } else if (isPalindromeTbl[prevIdx + 1][idx - 1]) {
                    isPalindromeTbl[prevIdx][idx] = true;
                    auto palindromeLen = idx - prevIdx + 1;
                    if (palindromeLen > longestPalindromLen) {
                        longestPalindromLen = palindromeLen;
                        longestPalindromeLoIdx = prevIdx;
                    }
                }
            }
            
            // Add current character location to table mapping chars to their index locations
            chrPrevIndicesV.emplace_back(idx);
        }
        
        return s.substr(longestPalindromeLoIdx, longestPalindromLen);
    }
    
    pair<int, int>
    palindromeSubstringsCenteredAroundStrIdx(string& s, int loIdx, int hiIdx) {
        
        // Palindrome extends over s[lo, hi]
        int lo = -1;
        int hi = -1;
        
        while ((loIdx >= 0) && (hiIdx < s.size())) {
            
            if (s[loIdx] != s[hiIdx]) {
                // Substring s[loIdx, hiIdx] no longer a palindrome
                // Hence new palindromes cannot be formed centered around this substring
                break;
            }
            
            // Substring s[loIdx, hiIdx] is a palindrome
            lo = loIdx;
            hi = hiIdx;
            
            // Extend the substring boundary by one char both to the left & right
            --loIdx, ++hiIdx;
        }
        
        return pair<int, int>(lo, hi);
    }
    
    string
    longestPalindromeViaCentering(string& s) {
        
        int longestPalindromLen = 0;
        int longestPalindromeLoIdx = -1;
        
        // Iterate over the string sequentially char by char. Determine
        // the even + odd len palindromes centered around single
        // char/2 char pairs; and track the boundary + length of the longest palindrome
        for (int i = 0; i < s.size(); ++i) {
            
            // Maximal odd length palindromes centered around char s[i]
            auto palindromeBounds = 
                palindromeSubstringsCenteredAroundStrIdx(s, i, i);
            auto palindromeLen = palindromeBounds.second - palindromeBounds.first + 1;
            if (palindromeLen > longestPalindromLen) {
                longestPalindromLen = palindromeLen;
                longestPalindromeLoIdx = palindromeBounds.first;
            }
            
            // Maximal even length palindromes centered around substring s[i, i + 1]
            palindromeBounds = 
                palindromeSubstringsCenteredAroundStrIdx(s, i, i + 1);
            palindromeLen = palindromeBounds.second - palindromeBounds.first + 1;
            if (palindromeLen > longestPalindromLen) {
                longestPalindromLen = palindromeLen;
                longestPalindromeLoIdx = palindromeBounds.first;
            }
        }
        
        return s.substr(longestPalindromeLoIdx, longestPalindromLen);
    }
    
};
