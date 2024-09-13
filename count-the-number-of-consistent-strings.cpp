// p => allowed.size(), q => words.size(), l => avg word length of strings in 'words'
// Time Complexity : O(p + ql)
// Space Complexity : O(p)

class Solution {
public:
    int
    countConsistentStrings(string allowed, vector<string>& words) {
        // Hash table of allowed chars in consistent string
        unordered_set<char> allowedCharsTbl(allowed.begin(), allowed.end());
        
        int nConsistentStrs = 0;
        // Iterate over each word
        for (auto & word : words) {
            // word is assumed as consistent initially
            bool consistentWord = true;
            // Iterate over each char of word; if any char is in the not allowed
            // bucket; mark word as inconsistent
            for (auto c : word) {
                if (allowedCharsTbl.find(c) == allowedCharsTbl.end()) {
                    consistentWord = false;
                    break;
                }
            }
            
            if (consistentWord) {
                // Current word is consistent
                ++nConsistentStrs;
            }
        }
        
        return nConsistentStrs;
    }
};
