// DP Bottom up
// Time Complexity : O(n)
// Space Complexity : O(n)

// DP Bottom up Space Optimized
// Time Complexity : O(n)
// Space Complexity : O(1)

// Use input contraints to build up a dependency graph with vertices as the
// various vowels {'a', 'e', 'i', 'o', 'u'} and edges as the
// dependencies/constraints placed on the list of vowel chars which can succeed/follow
// a particular vowel char. With this graph, one can easily make out the following
// 1. Vowel 'a' can preceeded only by vowels 'e' or 'i' or 'u'
// 2. Vowel 'e' can preceeded only by vowels 'a' or 'i'
// 3. Vowel 'i' can preceeded only by vowels 'e' or 'o'
// 4. Vowel 'o' can preceeded only by vowels 'i
// 5. Vowel 'u' can preceeded only by vowels 'i' or 'o'

const int moduloFactor = 1000000000 + 7;

class Solution {
public:
    int
    countVowelPermutation(int n) {
        //return countVowelPermutationBottomUpDp(n);
        return countVowelPermutationBottomUpDpSpaceOptimized(n);
    }

private:

    int
    countVowelPermutationBottomUpDp(int n) {
        if (0 == n) {
            // Base case of 0 len string
            return 0;
        }
    
        // dpTbl[strLen][lastChar] represents the number of permutations
        // with strings of length 'strLen' whose last letter is 'lastChar'.
        // Using a hash table instead of an 2D array as the number of permutations
        // for many of the 'lastChar' values would 0 (for consonants/non-vowels)
        unordered_map<int, map<char, int> > dpTbl;
         
        // Initialize for string length of 0/1 with last char being one of the vowels
        vector<char> vowelsV({'a', 'e', 'i', 'o', 'u'});
        for (auto c : vowelsV) {
            dpTbl[0][c] = 0;
            dpTbl[1][c] = 1;
        }
        
        // Compute num permutations for strings of length in the range [2, n]
        // iteratively incrementing the string length at each step
        for (int len = 2; len <= n; ++len) {
            
            // Vowel 'a' can preceeded only by vowels 'e' or 'i' or 'u' 
            long long nStrEndingWithA = 0;
            nStrEndingWithA += dpTbl[len - 1]['e'];
            nStrEndingWithA += dpTbl[len - 1]['i'];
            nStrEndingWithA += dpTbl[len - 1]['u'];
            dpTbl[len]['a'] = nStrEndingWithA % moduloFactor;

            // Vowel 'e' can preceeded only by vowels 'a' or 'i'
            long long nStrEndingWithE = 0;
            nStrEndingWithE += dpTbl[len - 1]['a'];
            nStrEndingWithE += dpTbl[len - 1]['i'];
            dpTbl[len]['e'] = nStrEndingWithE % moduloFactor;

            // Vowel 'i' can preceeded only by vowels 'e' or 'o'
            long long nStrEndingWithI = 0;
            nStrEndingWithI += dpTbl[len - 1]['e'];
            nStrEndingWithI += dpTbl[len - 1]['o'];
            dpTbl[len]['i'] = nStrEndingWithI % moduloFactor;
            
            // Vowel 'o' can preceeded only by vowels 'i'
            long long nStrEndingWithO = 0;
            nStrEndingWithO += dpTbl[len - 1]['i'];
            dpTbl[len]['o'] = nStrEndingWithO % moduloFactor;

            // Vowel 'u' can preceeded only by vowels 'i' or 'o'
            long long nStrEndingWithU = 0;
            nStrEndingWithU += dpTbl[len - 1]['i'];
            nStrEndingWithU += dpTbl[len - 1]['o'];
            dpTbl[len]['u'] = nStrEndingWithU % moduloFactor;
        }
        
        // Add up the total number of vowel strings of length 'n'
        long long nPermutations = 0;
        for (auto c : vowelsV) {
            nPermutations += dpTbl[n][c];
            nPermutations %= moduloFactor;
        }
        
        return nPermutations;
    }
    
    int
    countVowelPermutationBottomUpDpSpaceOptimized(int n) {
        if (0 == n) {
            // Base case of 0 len string
            return 0;
        }
    
        // dpTbl[strLen % 2][lastChar] represents the number of permutations
        // of strings of length 'strLen' whose last letter is 'lastChar'
        // Use vector<map<char, int> > if one wants to optimize on space as
        // the table entries would only be created for vowels chars
        // Use vector<vector<int> > if one wants to optimize on speed compared to
        // space as hash lookup is replaced by direct 2D array lookup
        //vector<map<char, int> > dpTbl(2);
        vector<vector<int> > dpTbl(2, vector<int>('a' + 26, 0));
        
        // Initialize permutation counts table for vowel strings of length 0/1
        vector<char> vowelsV({'a', 'e', 'i', 'o', 'u'});
        for (auto c : vowelsV) {
            dpTbl[0][c] = 0;
            dpTbl[1][c] = 1;
        }
        
        // Compute num permutations for strings of length in the range [2, n]
        // iteratively incrementing the string length at each step
        for (int len = 2; len <= n; ++len) {
            
            // For space optimization
            // len maps to len % 2
            int lenModulo2 = (len & 0x1);
            // (len - 1) maps to (len - 1) % 2
            int prevLenModulo2 = ((len - 1) & 0x1);
            
            // Vowel 'a' can preceeded only by vowels 'e' or 'i' or 'u' 
            long long nStrEndingWithA = 0;
            nStrEndingWithA += dpTbl[prevLenModulo2]['e'];
            nStrEndingWithA += dpTbl[prevLenModulo2]['i'];
            nStrEndingWithA += dpTbl[prevLenModulo2]['u'];
            dpTbl[lenModulo2]['a'] = nStrEndingWithA % moduloFactor;

            // Vowel 'e' can preceeded only by vowels 'a' or 'i'
            long long nStrEndingWithE = 0;
            nStrEndingWithE += dpTbl[prevLenModulo2]['a'];
            nStrEndingWithE += dpTbl[prevLenModulo2]['i'];
            dpTbl[lenModulo2]['e'] = nStrEndingWithE % moduloFactor;

            // Vowel 'i' can preceeded only by vowels 'e' or 'o'
            long long nStrEndingWithI = 0;
            nStrEndingWithI += dpTbl[prevLenModulo2]['e'];
            nStrEndingWithI += dpTbl[prevLenModulo2]['o'];
            dpTbl[lenModulo2]['i'] = nStrEndingWithI % moduloFactor;
            
            // Vowel 'o' can preceeded only by vowels 'i'
            long long nStrEndingWithO = 0;
            nStrEndingWithO += dpTbl[prevLenModulo2]['i'];
            dpTbl[lenModulo2]['o'] = nStrEndingWithO % moduloFactor;

            // Vowel 'u' can preceeded only by vowels 'i' or 'o'
            long long nStrEndingWithU = 0;
            nStrEndingWithU += dpTbl[prevLenModulo2]['i'];
            nStrEndingWithU += dpTbl[prevLenModulo2]['o'];
            dpTbl[lenModulo2]['u'] = nStrEndingWithU % moduloFactor;
        }
        
        // Add up the total number of vowel strings of length 'n'
        // ending with the vowels chars a, e, i, o, u
        long long nPermutations = 0;
        for (auto c : vowelsV) {
            nPermutations += dpTbl[(n & 0x1)][c];
            nPermutations %= moduloFactor;
        }
        
        return nPermutations;
    }
};
