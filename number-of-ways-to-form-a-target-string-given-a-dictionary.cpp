// nIndices => words[0].size(), tSize = target.size()
// nWords = words.size()
// Time complexity : O(nIndices X tSize) + O(nIndices X nWords)
// Space complexity : O(tSize)

class Solution {
public:
    int
    numWays(vector<string>& words, string target) {
        
        const int moduloFactor = 1000000000 + 7;
        // Target string size
        int tSize = target.size();
        // All words are of the same size
        int nIndices = words[0].size();
        
        vector<long> nWaysTbl(tSize + 1, 0);
        nWaysTbl[0] = 1;
        for (int idx = 0; idx < nIndices; ++idx) {            
            vector<int> idxChrFreqCntTbl(26, 0);
            for (auto & word : words) {
                auto & charAtIdx = word[idx];
                idxChrFreqCntTbl[charAtIdx - 'a']++;
            }
        
            for (int tgtIdx = tSize - 1; tgtIdx >= 0; --tgtIdx) {
                
                auto & tChar = target[tgtIdx];
                long nWaysToSelectTgtChr = idxChrFreqCntTbl[tChar - 'a'];
                long nWaysToBuildSubStr = (nWaysToSelectTgtChr * nWaysTbl[tgtIdx]);
                
                nWaysTbl[tgtIdx + 1] += nWaysToBuildSubStr;
                nWaysTbl[tgtIdx + 1] %= moduloFactor;
            }
        }
        
        return nWaysTbl[tSize];
    }
};
