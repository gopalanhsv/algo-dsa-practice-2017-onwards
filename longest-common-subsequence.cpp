class Solution {
public:
    int
    longestCommonSubsequence(string text1, string text2) {
        if (text1.empty() || text2.empty()) {
            // Base case of one of the two strings being empty
            // => no common subsequence
            return 0;
        }
        
        //return lcsDPApproach(text1, text2);
        return lcsDPApproachSpaceOptimized(text1, text2);
    }
    
private:
    
    int
    lcsDPApproach(string& text1, string& text2) {
        // String lengths
        int len1 = text1.size();
        int len2 = text2.size();
        
        // dpTbl(i, j) is the length of LCS of the two substrings
        // text1[0, i - 1] & text2[0, j - 1]
        vector<vector<int> > dpTbl(len1 + 1, vector<int>(len2 + 1, 0));
        // Compare the two input strings one char at a time
        
        // Current substring of text1 is text1[0, i - 2]. 
        // Adding char text1[i - 1] to the substring 
        for (int i = 1; i <= len1; ++i) {
            
            // Current substring of text2 is text2[0, j - 2]. 
            // Adding char text2[j - 1] to the substring 
            for (int j = 1; j <= len2; ++j) {
                
                // Assuming that the new char added to both the substrings
                // of text1 and text2 do not match; LCSLen(i, j) is initialized
                // to the max value of the common subsequence formed between 
                // 1. text1(0, i - 2) & text2(0, j - 2) OR
                // 2. text1(0, i - 2) & text2(0, j - 1) OR
                // 3. text1(0, i - 1) & text2(0, j - 2)
                dpTbl[i][j] = max(dpTbl[i - 1][j - 1],
                                  max(dpTbl[i - 1][j], dpTbl[i][j - 1]));
                
                if (text1[i - 1] == text2[j - 1]) {
                    // New char being added to both the substrings is equal;
                    // so len of common subsequence is updated by 1 to that
                    // of the subsequence formed between earlier substrings
                    // text1[0, i - 2] & text2[0, j - 2]
                    // Update the LCSLen(i, j) to the max possible value
                    dpTbl[i][j] = max(dpTbl[i][j],
                                      1 + dpTbl[i - 1][j - 1]);
                }
            }
        }
        
        return dpTbl[len1][len2];
    }
    
    int
    lcsDPApproachSpaceOptimized(string& text1, string& text2) {
        // String lengths
        int len1 = text1.size();
        int len2 = text2.size();
        
        // Technique is similar to above except that a space optimized
        // DP table is used which consists of just 2 rows; as calc for 
        // each row depends just on the previous row values
        
        // dpTbl(i, j) is the length of LCS of the two substrings
        // text1[0, i - 1] & text2[0, j - 1]
        vector<vector<int> > dpTbl(2, vector<int>(len2 + 1, 0));
        // Compare the two input strings one char at a time
        
        // Current substring of text1 is text1[0, i - 2]. 
        // Adding char text1[i - 1] to the substring 
        for (int i = 1; i <= len1; ++i) {
            
            // Current substring of text2 is text2[0, j - 2]. 
            // Adding char text2[j - 1] to the substring 
            for (int j = 1; j <= len2; ++j) {
                
                // Assuming that the new char added to both the substrings
                // of text1 and text2 do not match; LCSLen(i, j) is initialized
                // to the max value of the common subsequence formed between 
                // 1. text1(0, i - 2) & text2(0, j - 2) OR
                // 2. text1(0, i - 2) & text2(0, j - 1) OR
                // 3. text1(0, i - 1) & text2(0, j - 2)
                dpTbl[(i & 0x1)][j] = max(dpTbl[((i - 1) & 0x1)][j - 1],
                                          max(dpTbl[((i - 1) & 0x1)][j],
                                              dpTbl[(i & 0x1)][j - 1]));
                
                if (text1[i - 1] == text2[j - 1]) {
                    // New char being added to both the substrings is equal;
                    // so len of common subsequence is updated by 1 to that
                    // of the subsequence formed between earlier substrings
                    // text1[0, i - 2] & text2[0, j - 2]
                    // Update the LCSLen(i, j) to the max possible value
                    dpTbl[(i & 0x1)][j] = max(dpTbl[(i & 0x1)][j],
                                              1 + dpTbl[((i - 1) & 0x1)][j - 1]);
                }
            }
        }
        
        return dpTbl[(len1 & 0x1)][len2];
    }
};
