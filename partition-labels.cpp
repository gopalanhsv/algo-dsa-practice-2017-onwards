// O(string length) time
// O(1) space (hash table can have max 26 entries)

class Solution {
public:
    vector<int>
    partitionLabels(string s) {
        int strSz = s.size();
        // Create a hash table mapping each char in the string
        // to its rightmost index position in the string
        unordered_map<char, int> rightmostIdxTbl;
        for (int i = 0; i != strSz; ++i) {
            rightmostIdxTbl[s[i]] = i;
        }
        
        // Output vector of each of the partition sizes
        vector<int> partitionSzV;
        // Since string has to be partitioned into max number of pieces
        // with the given constraint (of all character instances being in
        // the same partition); adopt the greedy approach of making each
        // partition as small as possible. That is, if a new partition starts
        // at a particular char, attempt to end the partition at the leftmost
        // possible position (i.e. the rightmost instance of that char as all
        // instances of same char must be in single partition).
        // The above process of redefining the end of current partition has
        // to be done iteratively till all chars from start of current partition
        // till the redefined end of current partition get processed and the
        // current partition end stays fixed/does not get redefined due to
        // new char inclusion
        
        // Current partition defined by range [partitionStart, partitionEnd]
        int partitionStart = 0;
        int partitionEnd = 0;
        while (partitionEnd < strSz) {
            // Current position/char initialized to partition start
            int currIdx = partitionStart;
            // Set the partition end to rightmost location of current char
            // Advance current char position iteratively to include all
            // chars upto partition end -- which may get reset/advanced to
            // account for rightmost location of new current char
            while (currIdx <= partitionEnd) {
                auto & currChar = s[currIdx++];
                // Advance the partition end (if reqd) to account for 
                // rightmost location of current char extending beyond
                // the parition range end
                partitionEnd = max(partitionEnd, rightmostIdxTbl[currChar]);
            }
            
            // Compute current partition size and store
            partitionSzV.emplace_back(partitionEnd - partitionStart + 1);
            // Current partition has ended
            
            // Setup to explore the next partition 
            partitionStart = ++partitionEnd;
        }
        
        return partitionSzV;
    }
};
