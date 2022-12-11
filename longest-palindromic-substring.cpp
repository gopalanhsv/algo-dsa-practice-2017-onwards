class Solution {
public:
    string
    longestPalindrome(string s) {
        
        //return countSubstringsDPMemoization(s);
        return longestPalindromeViaCentering(s);
    }
    
private:
    
    int
    countSubstringsDPMemoization(string& s) {
        
        // String size
        int n = s.size();
        
        // DP memoization 2D table which tracks if a substring is a palindrome.
        // Entry _isPalindromeTbl[i][j] is true if the substring in the
        // closed range [i, j] is a palindrome, false otherwise
        vector<vector<int> > isPalindromeTbl(n, vector<int>(n, false));
    
        // Mapping from a string to index locations within the string
        // where the character is present
        unordered_map<char, vector<int> > chrToLocationTbl;
        
        int nPalindromes = 0;
        
        // Iterate over the string sequentially char by char
        for (int idx = 0; idx != n; ++idx) {
        
            auto & currChar = s[idx];
            
            // The current character by itself forms a single character palindrome
            // Update internal states to reflect the same
            ++nPalindromes;
            isPalindromeTbl[idx][idx] = true;
            
            // Current 
            
            // Check if addition of current character s[idx] to the substring s[0, idx - 1]
            // creates new palindromes. Addition of current char at s[idx] can form palindromes
            // only if the substring s[0, idx - 1] contains instance(s) of char s[idx]  
            auto & chrPrevIndicesV = chrToLocationTbl[currChar];
            // Get the locations of earlier instances of current character
            for (auto & prevIdx : chrPrevIndicesV) {
                // The substring between earlier instances of current character and
                // the current location (i.e s[prevIdx + 1, idx - 1] should be a palindrome
                // or null string. Then addition of s[idx] at right and s[prevIdx] will
                // make the entire substring s[prevIdx, idx] a new palindrome
                
                // If palindrome is formed, update the internal states
                if (idx - prevIdx == 1) {
                    ++nPalindromes;
                    isPalindromeTbl[prevIdx][idx] = true;
                } else if (isPalindromeTbl[prevIdx + 1][idx - 1]) {
                    ++nPalindromes;
                    isPalindromeTbl[prevIdx][idx] = true;
                }
            }
            
            // Add current character location to table mapping chars to their index locations
            chrPrevIndicesV.emplace_back(idx);
        }
        
        return nPalindromes;
    }
    
    pair<int, int>
    palindromeSubstringsCenteredAroundStrIdx(string& s, int loIdx, int hiIdx) {
        
        // Start and end indices of palindrome
        int palLoIdx = -1;
        int palHiIdx = -1;
        
        while (loIdx >= 0 && hiIdx < s.size()) {
            
            if (s[loIdx] != s[hiIdx]) {
                // Substring s[loIdx, hiIdx] no longer a palindrome
                // Hence new palindromes cannot be formed centered around this substring
                break;
            }
            
            // Substring s[loIdx, hiIdx] is a palindrome
            palLoIdx = loIdx;
            palHiIdx = hiIdx;
            
            // Advance the substring left boundary one char to left and
            // right boundary one char to right
            --loIdx, ++hiIdx;
        }
        
        return pair<int, int>(palLoIdx, palHiIdx);
    }
    
    string
    longestPalindromeViaCentering(string& s) {
        
        int longestPalindromLen = 0;
        int longestPalindromeLoIdx = -1;
        
        // Iterate over the string sequentially char by char. Determine
        // the even + odd len palindromes centered around single
        // char/2 char pairs; and track the boundary + length of the longest palindrome
        for (int i = 0; i < s.size(); ++i) {
            
            // Odd length palindromes centered around char s[i]
            auto palindromeBounds = 
                palindromeSubstringsCenteredAroundStrIdx(s, i, i);
            auto palindromeLen = palindromeBounds.second - palindromeBounds.first + 1;
            if (palindromeLen > longestPalindromLen) {
                longestPalindromLen = palindromeLen;
                longestPalindromeLoIdx = palindromeBounds.first;
            }
            
            // Even length palindromes centered around substring s[i, i + 1]
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
