// n => nums.size()
// Time complexity : O(n x n)
// Space complexity : O(1)

class Solution {
public:
    int
    longestArithSeqLength(vector<int>& nums) {
        int arrSz = nums.size();
        if (arrSz <= 2) {
            return arrSz;
        }
        
        return longestSeqLengthViaDPWorkingVersion(nums);
    }
    
private:
    
    int
    longestSeqLengthViaDP(vector<int>& nums) {
        int arrSz = nums.size();
        
        // dpTbl[idx][cdiff] is the longest length of an AP (arithmetic sequence/progression)
        // with a common difference of 'cdiff' and consisting only of subsequences formed in
        // the closed range [0, idx] with the last term being nums[idx]
        unordered_map<int, unordered_map<int, int> > dpTbl;
        // Maximum AP length seen so far
        int maxAPLen = 1;
        
        for (int currElemIdx = 0; currElemIdx < arrSz; ++currElemIdx) {
            auto & currTerm = nums[currElemIdx];
            //cout << "LT = " << lastTerm << endl;
            for (int prevElemIdx = 0; prevElemIdx < currElemIdx; ++prevElemIdx) {
                auto & prevTerm = nums[prevElemIdx];
                auto commonDiff = currTerm - prevTerm;
                //cout << "PT = " << secondLastTerm << endl;
                //cout << "CD = " << commonDiff << endl;
                int apSeqLen = dpTbl[prevElemIdx][commonDiff];
                if (0 == apSeqLen) {
                    apSeqLen = 1;
                }
                ++apSeqLen;
                //cout << "APLEN = " << apSeqLen << endl;
                maxAPLen = max(apSeqLen, maxAPLen);
                //if (dpTbl[currElemIdx][commonDiff] < apSeqLen) {
                    dpTbl[currElemIdx][commonDiff] = apSeqLen;
                //}
            }
        }
        
        return maxAPLen;
    }
    

    
    int
    longestSeqLengthViaDPWorkingVersion(vector<int>& nums) {
        int arrSz = nums.size();
        
        // dpTbl[idx][cdiff] is the longest length of an AP (arithmetic sequence/progression)
        // with a common difference of 'cdiff' and consisting only of subsequences formed in
        // the closed range [0, idx] with the last term being nums[idx]
        vector<unordered_map<int, int> > dpTbl(arrSz);
        // Maximum AP length seen so far
        int maxAPLen = 1;
        
        for (int currElemIdx = 0; currElemIdx < arrSz; ++currElemIdx) {
            auto & currTerm = nums[currElemIdx];
            for (int prevElemIdx = 0; prevElemIdx < currElemIdx; ++prevElemIdx) {
                auto & prevTerm = nums[prevElemIdx];
                auto commonDiff = currTerm - prevTerm;
                int apSeqLen = dpTbl[prevElemIdx][commonDiff];
                if (0 == apSeqLen) {
                    apSeqLen = 1;
                }
                ++apSeqLen;
                dpTbl[currElemIdx][commonDiff] = apSeqLen;
                maxAPLen = max(apSeqLen, maxAPLen);
            }
        }
        
        return maxAPLen;
    }
};
