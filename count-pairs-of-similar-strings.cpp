class Solution {
public:
    int
    similarPairs(vector<string>& words) {
        // Each word can represented by a fingreprint
        // capturing the chars present in the word
        // Similar words will have the same fingerprint
        // while dissimilar words have different fingerprint

        // Each word can be represented by a fingerprint bitmask wherein
        // bit positions 0 to 25 correspond to chars 'a' to 'z'
        // A 1-bit at position 'x' indicates the presence of
        // appropriate char while a 0-bit indicates the absence 

        // Tracks the count of words with a particular fingerprint
        unordered_map<unsigned int, int> fingerprintFreqCntTbl;
        int nPairs = 0;
        // Iterate over each word sequentially from L->R
        for (auto & word : words) {
            // Build fingerprint for current word
            unsigned int fpMask = 0;
            for (auto & c : word) {
                fpMask |= (1 << int(c - 'a'));
            }
            
            auto it = fingerprintFreqCntTbl.find(fpMask);
            if (it != fingerprintFreqCntTbl.end()) {
                // Words similar to current word seen earlier
                // Current word forms a pair with each of the
                // similar words seen earlier
                nPairs += (it->second);
                // Update freq cnt for fingerprint
                ++(it->second);
            } else {
                fingerprintFreqCntTbl[fpMask] = 1;
            }
        }
        
        return nPairs;
    }
};
