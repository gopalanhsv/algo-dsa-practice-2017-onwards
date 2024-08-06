// n => word.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    minimumPushes(string word) {
        // Only keys 2 to 9 can be mapped to letters, excluding others i.e. a total
        // of 9 - 2 + 1 = 8 keys
        // All the word letters need to mapped to the 8 distinct keys s.t. the number
        // of pushes required are minimum
        // Adopt the greedy approach for mapping letters to keys by mapping the most
        // frequent letter (from amongst the unassigned letters of the word) to a key
        // which is used/mapped the least  from amongst the 8 keys
        
        // Build frequency count table for each of the word letters
        vector<int> freqCntTbl(26, 0);
        for (auto & c : word) {
            freqCntTbl[int(c - 'a')]++;
        }
        
        // Build array of tuples of letter, frequency count pairs
        vector<pair<int, int> > letterFreqCntV;
        for (auto i = 0 ; i != 26; ++i) {
            if (freqCntTbl[i]) {
                letterFreqCntV.push_back({i, freqCntTbl[i]});
            }
        }
        // Sort the tuples in the descending order of respective frequency count
        sort(letterFreqCntV.begin(), letterFreqCntV.end(),
            [&](const auto & p1, const auto & p2){
                return p1.second > p2.second;
            });
        
        // Mapping from a key to number of unique letters assigned to respective key 
        const int nDistinctKeys = 8;
        vector<int> keyToNumLettersTbl(nDistinctKeys, 0);
        int nextAvlKeyId = 0;
        int nPushes = 0;
        // Assign keys to letters
        for (auto & ent : letterFreqCntV) {
            auto nLetterInstances = ent.second;
            // Number of pushes required for single instance of current letter
            int nPushesForLetter = ++keyToNumLettersTbl[nextAvlKeyId];
            nPushes += (nPushesForLetter * nLetterInstances);
            nextAvlKeyId++;
            nextAvlKeyId %= nDistinctKeys;
        }
        
        return nPushes;
    }
};
