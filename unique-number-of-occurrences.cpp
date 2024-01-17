// n => arr.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    bool
    uniqueOccurrences(vector<int>& arr) {
        if (arr.size() == 1) {
            // Base case of single element array
            return 1;
        }
        
        // Build frequency count table of elements
        unordered_map<int, int> freqCntTbl;
        for (auto & e : arr) {
            freqCntTbl[e]++;
        }

        // Iterate over the frequency count table elements
        // Build a hash table of the frequency counts to check duplicate frequency counts
        unordered_set<int> nOccurrencesTbl;
        for (auto & hte : freqCntTbl) {
            if (nOccurrencesTbl.find(hte.second) != nOccurrencesTbl.end()) {
                // Elements having same frequency counts found
                return false;
            }
            nOccurrencesTbl.insert(hte.second);
        }
        // All elems have unique frequency counts
        return true;
    }
};
