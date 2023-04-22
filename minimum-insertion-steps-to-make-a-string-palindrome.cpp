// String size = n
//
// Memoization approach
// Time complexity : O(n x n)
// Space complexity : O(n x n)
// DP approach
// Time complexity : O(n x n)
// Space complexity : O(n x n)
// DP optimized approach
// Time complexity : O(n x n)
// Space complexity : O(n)

class Solution {
public:
    int
    minInsertions(string s) {
        if (s.size() <= 1) {
            // Base case of empty/single char string
            return 0;
        }
        
        //return minInsertionsViaMemoization(s);
        //return minInsertionsViaDP(s);
        return minInsertionsViaDPOptimized(s);
    }
    
private:
    
    int
    minInsertionsViaMemoization(
        string& s, int lo, int hi, vector<vector<int> >& memoTbl) {
        
        // Determine the min insertions required to make substring s[lo, hi]
        // palindrome and store it in the cache
        
        if (lo >= hi) {
            // Single char substring/invalid range substring
            // No insertions require
            return 0;
        }
        
        if (-1 == memoTbl[lo][hi]) {
            // Min insertions required for substring s[lo, hi] is being computed for
            // the first time and then stored in cache
            int minInsertionsReqd = 0;
            if (s[lo] == s[hi]) {
                // Subtring end chars are identical. Need to compute min insertions
                // required to make enclosed substring s[lo + 1, hi - 1] palindromic
                minInsertionsReqd =
                    minInsertionsViaMemoization(s, lo + 1, hi - 1, memoTbl);
            } else {
                // Subtring end chars are non-identical. Two options to make 
                // subtring s[lo, hi] palindromic
                // 1. Split s[lo, hi] to s[lo] + s[lo + 1, hi]
                //    Insert s[lo] at end to get s[lo] + s[lo + 1, hi] + s[lo]
                //    Make s[lo + 1, hi] palindromic via insertions
                // 2. Split s[lo, hi] to s[lo, hi - 1] + s[hi]
                //    Insert s[hi] at beginning to get s[hi] + s[lo, hi - 1] + s[hi]
                //    Make s[lo, hi - 1] palindromic via insertions
                minInsertionsReqd =
                    1 + min(minInsertionsViaMemoization(s, lo, hi - 1, memoTbl),
                            minInsertionsViaMemoization(s, lo + 1, hi, memoTbl));
            }
            // Store min insertions reqd in cache
            memoTbl[lo][hi] = minInsertionsReqd;
        }
        
        // Cached result
        return memoTbl[lo][hi];
    }
    
    int
    minInsertionsViaMemoization(string& s) {
        int sLen = s.size();
        // memoTbl[i][j] caches the minimum insertions required to
        // make the substring s[i, j] a palindrome once its computed
        vector<vector<int> > memoTbl(sLen, vector<int>(sLen, -1));
        return minInsertionsViaMemoization(s, 0, sLen - 1, memoTbl);
    }
    
    int
    minInsertionsViaDP(string& s) {
        int sLen = s.size();
        // dpTbl[i][j] gives the minimum insertions required to
        // make the substring s[i, j] a palindrome
        vector<vector<int> > dpTbl(sLen, vector<int>(sLen, 0));
        
        // Determine the min insertions required to make the s[0, sLen - 1]
        // palindromic by progressively moving over the string from back to
        // front; computing the number of insertions required to make the
        // respective substrings till the end palindromic at each step
        
        // Iterate over the string from back to front sequentially 
        // fixing the start index of the substring at each step
        for (int lo = sLen - 1; lo >= 0; --lo) {
            // Single char substring s[lo, lo] is always palindromic
            dpTbl[lo][lo] = 0;
            // Iterate over the possible substring end indices for
            // current start position
            for (int hi = lo + 1; hi < sLen; ++hi) {
                // Min insertions required for substring s[lo, hi] making palindromic
                if (s[lo] == s[hi]) {
                    // Subtring end chars are identical. Need to compute min insertions
                    // required to make enclosed substring s[lo + 1, hi - 1] palindromic
                    dpTbl[lo][hi] = dpTbl[lo + 1][hi - 1];
                } else {
                    // Subtring end chars are non-identical. Two options to make 
                    // subtring s[lo, hi] palindromic
                    // 1. Split s[lo, hi] to s[lo] + s[lo + 1, hi]
                    //    Insert s[lo] at end to get s[lo] + s[lo + 1, hi] + s[lo]
                    //    Make s[lo + 1, hi] palindromic via insertions
                    // 2. Split s[lo, hi] to s[lo, hi - 1] + s[hi]
                    //    Insert s[hi] at beginning to get s[hi] + s[lo, hi - 1] + s[hi]
                    //    Make s[lo, hi - 1] palindromic via insertions
                    dpTbl[lo][hi] = 1 + min(dpTbl[lo][hi - 1], dpTbl[lo + 1][hi]);
                }
            }
        }
        return dpTbl[0][sLen - 1];
    }

    int
    minInsertionsViaDPOptimized(string& s) {
        int sLen = s.size();
        // dpTbl[i % 2][j] gives the minimum insertions required to
        // make the substring s[i, j] a palindrome
        // Using a space optimized version of the DP table with only 2 rows
        // (compared to the one in the function minInsertionsViaDPOptimized())
        vector<vector<int> > dpTbl(2, vector<int>(sLen, 0));
        
        // Determine the min insertions required to make the s[0, sLen - 1]
        // palindromic by progressively moving over the string from back to
        // front; computing the number of insertions required to make the
        // respective substrings till the end palindromic at each step
        
        // Iterate over the string from back to front sequentially 
        // fixing the start index of the substring at each step
        for (int lo = sLen - 1; lo >= 0; --lo) {
            // Single char substring s[lo, lo] is always palindromic
            dpTbl[(lo & 0x1)][lo] = 0;
            // Iterate over the possible substring end indices for
            // current start position
            for (int hi = lo + 1; hi < sLen; ++hi) {
                // Min insertions required for substring s[lo, hi] making palindromic
                if (s[lo] == s[hi]) {
                    // Subtring end chars are identical. Need to compute min insertions
                    // required to make enclosed substring s[lo + 1, hi - 1] palindromic
                    dpTbl[(lo & 0x1)][hi] = dpTbl[(lo + 1) & 0x1][hi - 1];
                } else {
                    // Subtring end chars are non-identical. Two options to make 
                    // subtring s[lo, hi] palindromic
                    // 1. Split s[lo, hi] to s[lo] + s[lo + 1, hi]
                    //    Insert s[lo] at end to get s[lo] + s[lo + 1, hi] + s[lo]
                    //    Make s[lo + 1, hi] palindromic via insertions
                    // 2. Split s[lo, hi] to s[lo, hi - 1] + s[hi]
                    //    Insert s[hi] at beginning to get s[hi] + s[lo, hi - 1] + s[hi]
                    //    Make s[lo, hi - 1] palindromic via insertions
                    dpTbl[(lo & 0x1)][hi] =
                        1 + min(dpTbl[(lo & 0x1)][hi - 1], dpTbl[(lo + 1) & 0x1][hi]);
                }
            }
        }
        return dpTbl[0][sLen - 1];
    }
};
