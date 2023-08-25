// n1 => s1.size(), n2 => s2.size()
// Time complexity : O(n1 x n2)
// Space complexity : O(n1 x n2)
class Solution {
public:
    bool
    isInterleave(string s1, string s2, string s3) {
        int len1 = s1.size();
        int len2 = s2.size();
        int len3 = s3.size();
        if (len1 + len2 != len3) {
            // Base case of length mismatch between s3 and its component strings s1, s2
            return false;
        }
        
        return isInterleavedDpIterative(s1, s2, s3);
    }
    
private:
    
    bool
    isInterleavedDpIterative(string& s1, string& s2, string& s3) {
        int len1 = s1.size();
        int len2 = s2.size();
        
        // dpTbl[len1][len2] is 'true' if the substring s3[0, len1 + len2 - 1] can be formed by
        // interleaving the two substrings s1[0, len1 - 1] and s2[0, len2 - 1]; and 'F' otherwise
        vector<vector<bool> > dpTbl(len1 + 1, vector<bool>(len2 + 1, false));
        
        // Base case of null substring s3 being formed from the two null substrings s1 & s2
        dpTbl[0][0] = true;
        
        // Determine if it is possible to form substring s3[0, i - 1] using
        // the substring s1[0, i - 1] for all possible lengths of 's1'
        // Increment the substring s1[0, i - 1] length sequentially    
        for (int i = 1; i <= len1; ++i) {
            if (s1[i - 1] == s3[i - 1]) {
                dpTbl[i][0] = dpTbl[i - 1][0];
            } 
        }
        
        // Determine if it is possible to form substring s3[0, i - 1] using
        // the substring s2[0, i - 1] for all possible lengths of 's2'
        // Increment the substring s2[0, i - 1] length sequentially 
        for (int j = 1; j <= len2; ++j) {
            if (s2[j - 1] == s3[j - 1]) {
                dpTbl[0][j] = dpTbl[0][j - 1];
            }
        }
        
        // Determine if it is possible to form substring s3[0, i + j - 1] by
        // interleaving the substrings s1[0, i - 1] and s2[0, j - 1]
        // Increment the length of substring s1[0, i - 1] sequentially 
        for (int i = 1; i <= len1; ++i) {
            // Increment the length of substring s2[0, j - 1] sequentially
            for (int j = 1; j <= len2; ++j) {
                
                // Determine if substrings s1[0, i - 1] & s2[0, j - 1] can be interleaved
                // to form substring s3[0, i + j - 1]
                
                bool s1Ands3LastCharsMatch = (s1[i - 1] == s3[i + j - 1]);
                bool s2Ands3LastCharsMatch = (s2[j - 1] == s3[i + j - 1]);
                
                if (s1Ands3LastCharsMatch) {
                    // Since last chars of substrings s1[0, i - 1] and s3[0, i + j - 1] are identical,
                    // interleaving is possible if s3[0, i - 1 + j - 1] can be formed by interleaving
                    // substrings s1[0, i - 2] & s2[0, j - 1]
                    dpTbl[i][j] = dpTbl[i - 1][j];
                } 
                
                if (!dpTbl[i][j] && s2Ands3LastCharsMatch) {
                    // Since last chars of substrings s2[0, j - 1] and s3[0, i + j - 1] are identical,
                    // interleaving is possible if s3[0, i + j - 1 - 1] can be formed by interleaving
                    // substrings s1[0, i - 1] & s2[0, j - 2]
                    dpTbl[i][j] = dpTbl[i][j - 1];
                }
            }
        }
        
        return dpTbl[len1][len2];
    }
};
