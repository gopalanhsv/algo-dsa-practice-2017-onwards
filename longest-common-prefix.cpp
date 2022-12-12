class Solution {
public:
    string
    longestCommonPrefix(vector<string>& strs) {
        // Base case of no string, single string
        if (strs.empty()) {
            return "";
        }
        if (1 == strs.size()) {
            return strs[0];
        }
        
        
        //return longestCommonPrefixViaHorizontalScan(strs);
        return longestCommonPrefixViaVerticalScan(strs);
    }
    
private:
    
    string
    longestCommonPrefixViaHorizontalScan(vector<string>& strs) {
        // Initialize the prefix as first string
        string prefix(strs[0]);
        typedef string::size_type strSzT;
        strSzT pfxLen = prefix.size();
        
        // Iterate over each of the remaining strings sequentially
        // For each iteration over a new string; keep only the portion
        // of the prefix which has an exact match with the starting
        // chars of the new string as we are looking for the
        // longest common prefix
        for (auto & str : strs) {
            
            // Update the current running prefix length to account
            // for shorter length of current string being evaluated
            pfxLen = min(pfxLen, str.size());
            strSzT i = 0;
            // Compare the chars of current prefix with the starting
            // chars of the current string. Retain the prefix only upto
            // the point till chars match
            while (i < pfxLen) {
                if (prefix[i] != str[i]) {
                    pfxLen = i;
                    break;
                }
                ++i;
            }
        }
        
        return prefix.substr(0, pfxLen);
    }
    
    string
    longestCommonPrefixViaVerticalScan(vector<string>& strs) {
        // Initialize prefix to the first string
        typedef string::size_type strSzT;
        auto & prefix = strs[0];
        strSzT pfxLen = prefix.size();
        // First compare all the 1st character of each string in vector,
        // then 2nd character of each string in vector,
        // then 3rd character of each string in vector and so on till
        // the last character (at most compare the minimum string length 
        // across all strings)
        // Keep doing the above, till a character mismatch occurs at a
        // particular character location -- the longest common prefix
        // is uptill the previous character location
        
        // Iteration over character indices sequentially
        for (strSzT idx = 0; idx < pfxLen; ++idx) {
            // Iteration over the characters at location 'idx'
            // across all strings
            for (int strId = 1; strId != strs.size(); ++strId) {
                auto & currString = strs[strId];
                if (currString[idx] != prefix[idx]) {
                    pfxLen = idx;
                    return prefix.substr(0, pfxLen);
                }
            }
        }
        
        return prefix;
    }
};
