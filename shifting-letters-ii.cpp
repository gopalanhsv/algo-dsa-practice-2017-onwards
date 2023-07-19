// Time complexity : O(s.size()) / O(n)
// Space complexity : O(s.size()) / O(n)

class Solution {
public:
    string
    shiftingLetters(string s, vector<vector<int>>& shifts) {
        int strSz = s.size();
        
        // Iterate over all shift entries. Compute the net shift
        // to be applied at each string position/index applying
        // the prefix sum paradigm
        vector<long> deltaShiftV(strSz + 1, 0);
        for (auto & shift : shifts) {
            auto & sIdx = shift[0];
            auto & eIdx = shift[1];
            auto & dir = shift[2];
            
            if (1 == dir) {
                // For each char in the range [sIdx, eIdx], the shift is
                // is +1 =>
                // Delta of +1 is applied to net shift at 'sIdx' so that
                // all chars from 'sIdx' onwards have forward shift in
                // addition to whatever shift they have
                deltaShiftV[sIdx] += 1;
                // Delta of -1 is applied to net shift at 'eIdx + 1' so that
                // all chars from 'eIdx + 1' onwards can have the forward
                // shift applied at 'sIdx' negated
                deltaShiftV[eIdx + 1] -= 1;
            } else {
                // Delta of -1 is applied to net shift at 'sIdx' so that
                // all chars from 'sIdx' onwards have backward shift in
                // addition to whatever shift they have
                deltaShiftV[sIdx] -= 1;
                // Delta of +1 is applied to net shift at 'eIdx + 1' so that
                // all chars from 'eIdx + 1' onwards can have the backward
                // shift applied at 'sIdx' negated
                deltaShiftV[eIdx + 1] += 1;
            }
        }
        
        // Apply the shift operation at each position of the string as
        // per the computed net shift at each index location
        int netShiftAtCurrIdx = 0;
        for (int idx = 0; idx != strSz; ++idx) {
            netShiftAtCurrIdx += deltaShiftV[idx];
            applyShiftToChar(s[idx], netShiftAtCurrIdx);
        }
        
        return s;
    }
    
private:
    
    inline void
    applyShiftToChar(char& c, int shift) {
        // Convert -ve shift to equivalent +ve shift
        while (shift < 0) {
            shift += 26;
        }
        // Offset from base char 'a'
        auto offset = int(c - 'a');
        // Offset after application of shift
        offset += shift;
        // Normalize to lowercase range of chars
        offset %= 26;
        // Compute shifted char
        c = 'a' + offset;
    }
};
