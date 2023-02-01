class Solution {
public:
    bool
    areSentencesSimilar(vector<string>& sentence1, vector<string>& sentence2,
                        vector<vector<string>>& similarPairs) {
        
        // Base case of sentences being not the same length
        if (sentence1.size() != sentence2.size()) {
            return false;
        }
        
        // Create a hash table of the word mappings for similar pairs
        // (both forward and reverse mapping)
        // Note multiple words may map to same word; or same word
        // may map to multiple words
        unordered_map<string, unordered_set<string> > similarWordsTbl;
        for (auto & sp : similarPairs) {
            similarWordsTbl[sp[0]].insert(sp[1]);
            similarWordsTbl[sp[1]].insert(sp[0]);
        }
        
        // Iterate over the words in sentence1 sequentially. Check if
        // word at same location in sentence2 is a similar pair of
        // the current word in sentence1
        unordered_map<string, unordered_set<string> >::iterator tblItr1, tblItr2, 
            tblEndItr = similarWordsTbl.end();
        for (int i = 0; i != sentence1.size(); ++i) {
            auto & s1Word = sentence1[i];
            auto & s2Word = sentence2[i];
            // The current words in sentence 1 and 2 are disimilar if either of
            // them do not map to the correct counterpart word in hash table or
            // are not same
            if (s1Word == s2Word) {
                continue;
            }
            tblItr1 = similarWordsTbl.find(s1Word);
            tblItr2 = similarWordsTbl.find(s2Word);
            if (tblItr1 == tblEndItr || tblItr2 == tblEndItr) {
                // Either of the two words in sentence doesn't have an
                // entry in the similar words table
                return false;
            }
            
            // Word in sentence 1 should be found against the entry for
            // word in sentence 2 in hash table; and vice versa
            auto & word1Set = tblItr1->second;
            auto & word2Set = tblItr2->second;
            
            if (word1Set.end() == word1Set.find(s2Word) || 
                word2Set.end() == word2Set.find(s1Word)) {
                // The current words in sentences 1 and 2 are disimilar as per
                // similar words hash table
                return false;
            }
        }
        return true;
    }
};
