// n => A.size() = B.size()
// Time Complexity : O(n)
// Space Complexity : O(n)
class Solution {
public:
    vector<int>
    findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        // Since both 'A' & 'B' are permutations of [1, n], each of the
        // numbers occurs once in both. All numbers which are common 
        // across A[0, i] & B[0, i] would have occurred twice in [0, i]

        auto n = A.size();
        // pfxFreqCntTbl[i] tracks the occurence count of numbers which
        // have been seen across in A[0, i] or B[0, i]
        vector<int> pfxFreqCntTbl(n + 1, 0);
        vector<int> pfxCommonV(n);
        int nCommonPfxSeenSoFar = 0;
        for (auto i = 0; i < n; ++i) {
            if (++pfxFreqCntTbl[A[i]] == 2) {
                ++nCommonPfxSeenSoFar;
            }
            if (++pfxFreqCntTbl[B[i]] == 2) {
                ++nCommonPfxSeenSoFar;
            }
            pfxCommonV[i] = nCommonPfxSeenSoFar;
        }
        return pfxCommonV;
    }
};
