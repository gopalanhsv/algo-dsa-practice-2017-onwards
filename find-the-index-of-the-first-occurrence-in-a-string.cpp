class Solution {
public:
    int
    strStr(string haystack, string needle) {
        // Base case for empty needle
        if (needle.empty()) {
            return 0;
        }
        // Empty haystack or haystack smaller than needle
        if (haystack.empty() || needle.size() > haystack.size()) {
            return -1;
        }
        
        typedef string::size_type strSzT;
        strSzT hSz = haystack.size();
        strSzT nSz = needle.size();
        // Iterate over each location of the haystack sequentially
        // from L->R where the a needle can commence
        strSzT searchEndPos = hSz - nSz;
        for (strSzT hPos = 0; hPos <= searchEndPos; ++hPos) {
            // hPos => haystack start position
            
            // Search for occurrence of first character match between
            // haystack and needle in haystack     
            if (haystack[hPos] == needle[0]) {            
                // Now check for match of other chars between haystack and needle
                strSzT hIdx = hPos + 1;
                strSzT nIdx = 1;
                while ((nIdx < nSz) && (haystack[hIdx] == needle[nIdx])) {
                     ++hIdx, ++nIdx;
                }
                if (nIdx == nSz) {
                    return hPos;
                }
            }
        }
        return -1;
    }
};
