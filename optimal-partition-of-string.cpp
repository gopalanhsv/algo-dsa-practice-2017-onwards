// Time complexity
// O(string size)
// Space complexity
// O(1)

class Solution {
public:
    int
    partitionString(string s) {
        int nPartitions = 0;
        
        // Bit vector tracking the chars seen so far in
        // current running partition
        unsigned int seenCharsBitVec = 0;
        // Iterate over the string chars sequentially from L->R
        for (auto & c : s) {
            unsigned int currCharBitPos = 1 << (c - 'a');
            if ((seenCharsBitVec & currCharBitPos) != 0) {
                // Current char was seen earlier in the current running partition
                // substring. Since each char can appear only once per partition
                // substring; terminate the current running partition at the
                // previous index/char and commence a new partition substring from
                // current char
                seenCharsBitVec = currCharBitPos;
                // Increment the number of partitions completed so far
                ++nPartitions;
            } else {
                seenCharsBitVec |= currCharBitPos;
            }
        }
        
        // Account for the last partition substring
        if (seenCharsBitVec) {
            ++nPartitions;
        }
        
        return nPartitions;
    }
};
