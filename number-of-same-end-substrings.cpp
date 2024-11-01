// n => s.size(), q => queries.size()
// Time Complexity : O(n + q)
// Time Complexity : O(n)

class Solution {
public:
    vector<int>
    sameEndSubstringCount(string s, vector<vector<int>>& queries) {
        auto strSz = s.size();
        
        // nPrefixCharsTbl[c][i] is the occurence count of chars of value 'c'
        // in the substring s[0, i - 1]
        // Iterate over the string sequentially from L->R and populate the
        // prefix count for each char at every location
        vector<vector<int> > nPrefixCharsTbl(26, vector<int>(strSz + 1, 0));
        nPrefixCharsTbl[s[0] - 'a'][1]++;
        for (auto i = 1; i < strSz; ++i) {
            for (auto c = 0 ; c < 26; ++c) {
                nPrefixCharsTbl[c][i + 1] = nPrefixCharsTbl[c][i];
            }
            nPrefixCharsTbl[s[i] - 'a'][i + 1]++;
        }
        
        auto nQueries = queries.size();
        vector<int> answersV(nQueries);
        // Iterate over each query
        for (auto qIdx = 0; qIdx < nQueries; ++qIdx) {
            auto l = queries[qIdx][0];
            auto r = queries[qIdx][1];
            int nSameEndSubStrs = 0;
            // Iterate over each possible char which can occur in the substring s[l, r]
            for (auto c = 0; c < 26; ++c) {
                // Count chars of type 'a' + c in substring s[l, r]
                int nChars = nPrefixCharsTbl[c][r + 1] - nPrefixCharsTbl[c][l];
                // If ocurrence count of char 'c' is 'n' in substring s[l, r],
                // Each occurence will form a total of 'n' same end substr with self
                // 1st occurence will form 'n - 1' same end substr with the succeeding 'n - 1' occurences
                // 2nd occurence will form 'n - 2' same end substr with the succeeding 'n - 2' occurences
                // 3rd occurence will form 'n - 3' same end substr with the succeeding 'n - 3' occurences
                // ......................................................................................
                // 'n - 1'th occurence will form '1' same end substr with the succeeding '1' occurences
                // Total number of same end substrs = 1 + 2 + ..... + n => AP
                nSameEndSubStrs += ((nChars * (nChars + 1)) / 2);
            }
            
            answersV[qIdx] = nSameEndSubStrs;
        }
        return answersV;
    }
};
