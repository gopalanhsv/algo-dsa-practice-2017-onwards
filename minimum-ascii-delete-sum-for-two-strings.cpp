// p => s1.size(), q => s2.size()

// Bottom up DP iterative :
// Time complexity : O(mn)
// Space complexity : O(mn)

// Bottom up DP iterative space optimized :
// Time complexity : O(mn)
// Space complexity : O(min(m, n))

class Solution {
public:
    int
    minimumDeleteSum(string s1, string s2) {
        //return minimumDeleteViaDP(s1, s2);
        return minimumDeleteViaDPSpaceOptimized(s1, s2);
    }
    
private:
    
    int
    minimumDeleteViaDP(string& s1, string& s2) {
        
        int s1Sz = s1.size();
        int s2Sz = s2.size();

        // dpTbl[i][j] => minimum ASCII delete sum for the two
        // substring s1[0, i - 1], s2[0, j - 1]
        vector<vector<int> > dpTbl(
            s1Sz + 1, vector<int>(s2Sz + 1, 0));
        
        // Minimum ASCII delete sum between s1[0, s1Idx - 1] and empty substring s2
        // would be the sum of all ASCII chars in s1[0, s1Idx - 1], as all chars in
        // s1 substring have to be deleted
        for (int s1Idx = 1; s1Idx <= s1Sz; ++s1Idx) {
            dpTbl[s1Idx][0] =
                dpTbl[s1Idx - 1][0] + int(s1[s1Idx - 1]);
        }
        // Minimum ASCII delete sum between s2[0, s2Idx - 1] and empty substring s1
        // would be the sum of all ASCII chars in s2[0, s2Idx - 1], as all chars in
        // s2 substring have to be deleted
        for (int s2Idx = 1; s2Idx <= s2Sz; ++s2Idx) {
            dpTbl[0][s2Idx] =
                dpTbl[0][s2Idx - 1] + int(s2[s2Idx - 1]);
        }
        
        // Iterate over all indices of string s1 sequentially
        for (int s1Idx = 1; s1Idx <= s1Sz; ++s1Idx) {
            // Iterate over all indices of string s2 sequentially
            for (int s2Idx = 1; s2Idx <= s2Sz; ++s2Idx) {
                // Compute minimum ASCII delete sum between the substrings
                // s1[0, s1Idx - 1] & s2[0, s2Idx - 1]
                int minDelSum = 0;
                if (s1[s1Idx - 1] == s2[s2Idx - 1]) {
                    // Same chars => min sum will identical to that between
                    // the substrings prior to current chars i.e between
                    // s1[0, s1Idx - 2] & s2[0, s2Idx - 2]
                    minDelSum = dpTbl[s1Idx - 1][s2Idx - 1];
                } else {
                    // Different chars => min sum will be min of the foll options:-
                    // (1) Delete both chars and find the min delete sum between
                    //     the substrings s1[0, s1Idx - 2] & s2[0, s2Idx - 2]
                    // (2) Delete s1[s1Idx - 1] and find the min delete sum between
                    //     the substrings s1[0, s1Idx - 2] & s2[0, s2Idx - 1]
                    // (3) Delete s2[s2Idx - 1] and find the min delete sum between
                    //     the substrings s1[0, s1Idx - 1] & s2[0, s2Idx - 2]
                    minDelSum = 
                        min(int(s1[s1Idx - 1]) + dpTbl[s1Idx - 1][s2Idx],
                            int(s2[s2Idx - 1]) + dpTbl[s1Idx][s2Idx - 1]);
                    minDelSum = 
                        min(minDelSum,
                            int(s1[s1Idx - 1]) + int(s2[s2Idx - 1]) +
                            dpTbl[s1Idx - 1][s2Idx - 1]);
                }
                dpTbl[s1Idx][s2Idx] = minDelSum;
            }
        }

        return dpTbl[s1Sz][s2Sz];
    }
    
    int
    minimumDeleteViaDPSpaceOptimized(string& s1, string& s2) {
        
        int s1Sz = s1.size();
        int s2Sz = s2.size();
        // Make s2 the shorter string for space optimization (lesser number of cols in DpTbl)
        if (s1Sz > s2Sz) {
            swap(s1, s2);
            swap(s1Sz, s2Sz);
        }
        
        // dpTbl[i][j] => minimum ASCII delete sum for the two
        // substring s1[0, i - 1], s2[0, j - 1]
        // Reorganizing the DP TBL here to have only two 2 rows as computation of
        // each result for current row depends on the previous row results. Flip
        // between 2 rows (current and other previous) for result calc via modulo-2 ops
        vector<vector<int> > dpTbl(2, vector<int>(s2Sz + 1, 0));
        
        // Minimum ASCII delete sum between s2[0, s2Idx - 1] and empty substring s1
        // would be the sum of all ASCII chars in s2[0, s2Idx - 1], as all chars in
        // s2 substring have to be deleted
        for (int s2Idx = 1; s2Idx <= s2Sz; ++s2Idx) {
            dpTbl[0][s2Idx] =
                dpTbl[0][s2Idx - 1] + int(s2[s2Idx - 1]);
        }
        
        // Iterate over all indices of string s1 sequentially
        for (int s1Idx = 1; s1Idx <= s1Sz; ++s1Idx) {

            // Minimum ASCII delete sum between s1[0, s1Idx - 1] and empty substring s2
            // would be the sum of all ASCII chars in s1[0, s1Idx - 1], as all chars in
            // s1 substring have to be deleted 
            dpTbl[(s1Idx & 0x1)][0] =
                dpTbl[(s1Idx - 1) & 0x1][0] + int(s1[s1Idx - 1]);
            
            // Iterate over all indices of string s2 sequentially
            for (int s2Idx = 1; s2Idx <= s2Sz; ++s2Idx) {
                // Compute minimum ASCII delete sum between the substrings
                // s1[0, s1Idx - 1] & s2[0, s2Idx - 1]
                int minDelSum = 0;
                if (s1[s1Idx - 1] == s2[s2Idx - 1]) {
                    // Same chars => min sum will identical to that between
                    // the substrings prior to current chars i.e between
                    // s1[0, s1Idx - 2] & s2[0, s2Idx - 2]
                    minDelSum = dpTbl[((s1Idx - 1) & 0x1)][s2Idx - 1];
                } else {
                    // Different chars => min sum will be min of the foll options:-
                    // (1) Delete both chars and find the min delete sum between
                    //     the substrings s1[0, s1Idx - 2] & s2[0, s2Idx - 2]
                    // (2) Delete s1[s1Idx - 1] and find the min delete sum between
                    //     the substrings s1[0, s1Idx - 2] & s2[0, s2Idx - 1]
                    // (3) Delete s2[s2Idx - 1] and find the min delete sum between
                    //     the substrings s1[0, s1Idx - 1] & s2[0, s2Idx - 2]
                    minDelSum = 
                        min(int(s1[s1Idx - 1]) + dpTbl[(s1Idx - 1) & 0x1][s2Idx],
                            int(s2[s2Idx - 1]) + dpTbl[(s1Idx & 0x1)][s2Idx - 1]);
                    minDelSum = 
                        min(minDelSum,
                            int(s1[s1Idx - 1]) + int(s2[s2Idx - 1]) +
                            dpTbl[(s1Idx - 1) & 0x1][s2Idx - 1]);
                }
                dpTbl[(s1Idx & 0x1)][s2Idx] = minDelSum;
            }
        }

        return dpTbl[(s1Sz & 0x1)][s2Sz];
    }
};
