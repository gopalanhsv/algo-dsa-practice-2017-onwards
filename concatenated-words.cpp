class Solution {
public:
    vector<string>
    findAllConcatenatedWordsInADict(vector<string>& words) {
        // Since a concatenated word is always made up of constituent words of
        // smaller size than it, sort the word array in the ascending order
        // of word lengths. At each index 'i' in the sorted array, the word
        // words[i] will be a concatenated word only if it can be built up/broken
        // into words which come prior to it i.e. in the range words[0, i - 1]
        
        // Sort the words in the ascending order of word lengths
        sort(words.begin(), words.end(),
             [&](auto & w1, auto & w2) {
                 return w1.size() < w2.size();
             });
        
        // Output array of concatenated words
        vector<string> concatWordsV;
        // Hash table of words seen so far
        unordered_set<string> seenWordsTbl;
        // Iterate over the sorted array sequentially in ascending order of word size
        for (auto & word : words) {
            if (!seenWordsTbl.empty()) {
                if (isConcatenatedWord(word, seenWordsTbl)) {
                    // Current word is concatenated from earlier seen words
                    concatWordsV.emplace_back(word);
                }
            }

            // Add current word to earlier seen words hash table
            seenWordsTbl.insert(word);
        }
        
        return concatWordsV;
    }
    
private:
    
    bool
    isConcatenatedWord(string& w, unordered_set<string>& seenWordsTbl) {
        int wordSz = w.size();
        vector<bool> dpTbl(wordSz + 1, false);
        dpTbl[0] = true;
        
        for (int i = 1; i <= wordSz; ++i) {
            for (int j = 0; j < i; ++j) {
                
                if (dpTbl[j]) {
                    auto remSubStr = w.substr(j, i - j);
                    auto it = seenWordsTbl.find(remSubStr);
                    if (it != seenWordsTbl.end()) {
                        dpTbl[i] = true;
                        break;
                    }
                }
                
            }
        }
        
        return dpTbl[wordSz];
    }
};
