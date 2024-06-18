// p => s.size(), q => t.size()
// Time complexity : O(max(p, q))
// Space complexity : O(1)

class Solution {
public:
    int
    findPermutationDifference(string s, string t) {
        
        // Since each char occurs at most once in 's', build hash table
        // of the sole locations for each of the chars in 's' 
        vector<int> charPosTbl(26, -1);
        for (auto i = 0; i != s.size(); ++i) {
            charPosTbl[int(s[i] - 'a')] = i;
        }
        
        // Iterate over each char in 't'
        int permDiff = 0;
        for (auto i = 0; i != t.size(); ++i) {
            auto & c = t[i];
            // Determine the absolute diff between indices of 'c'
            // in 's' & 't' if its pressent in both; and update
            // the permutation difference
            auto charPosInS = charPosTbl[int(c - 'a')];
            if (-1 != charPosInS) {
                permDiff += abs(i - charPosInS);
            }
        }
        
        return permDiff;
    }
};
