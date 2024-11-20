// n => s.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    int
    takeCharacters(string s, int k) {
        if (0 == k) {
            // Base case of no removals reqd
            return 0;
        }
        
        // The removed chars (min. 'k' of each a/b/c) can be deleted in one
        // of the following 3 ways:-
        // (1) Only from left of string
        // (Modeled by a window commencing at string left extending towards right)
        // (2) Only from right of string
        // (Modeled by a window ending at string string extending towards left)
        // (3) From both string left and right
        // (Modeled by a window commencing near string right extending toward right;
        // then circularly wrapping around to string left ending prior to window start)
        
        // Number of minutes reqd = number of removed chars
        // The above reduces the problem to finding the maximum sized variable sliding
        // window within the string whose characters are retained, i.e. the maximum
        // sized window s.t. there exist a min of 'k' chars each of a, b & c outside the window

        auto strSz = s.size();
        // Build hash table tracking the frequency count of chars within string
        vector<int> strFreqCntTbl(3, 0);
        for (auto i = 0; i != strSz; ++i) {
            strFreqCntTbl[s[i] - 'a']++;
        }

        if (strFreqCntTbl[0] < k || strFreqCntTbl[1] < k || strFreqCntTbl[2] < k) {
            // String contains less than 'k' chars of either a/b/c => removal infeasible
            return -1;
        }
        
        // Hash table tracking the frequency count of chars within window
        vector<int> winFreqCntTbl(3, 0);
        auto maxRetainedWinSz = 0;
        auto winStart = 0;
        // Iterate over the string from L->R sequentially adding chars to be retained
        // Substring chars to be retained extends over [winStart, winEnd]
        for (auto winEnd = 0; winEnd < strSz; ++winEnd) {
            // Add new char to window
            auto & c = s[winEnd];
            ++winFreqCntTbl[c - 'a'];
            
            // Shrink window from its left/start till the substring outside the
            // retained chars window contains a minimum of 'k' chars of a, b & c
            while ((winStart <= winEnd) &&
                   (strFreqCntTbl[0] - winFreqCntTbl[0] < k) ||
                   (strFreqCntTbl[1] - winFreqCntTbl[1] < k) || 
                   (strFreqCntTbl[2] - winFreqCntTbl[2] < k)) {
                
                // Update frequency count of retained chars
                --winFreqCntTbl[s[winStart++] - 'a'];
            }
            
            // Update max retained substring window size 
            auto retainedWinSz = winEnd - winStart + 1;
            maxRetainedWinSz = max(maxRetainedWinSz, retainedWinSz);
        }

        // Min sized substring satisfying 'k' criteria will consist of the
        // string chars lying outside the max sized window
        return strSz - maxRetainedWinSz;
    }
};
