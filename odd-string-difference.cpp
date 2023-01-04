class Solution {
public:
    string
    oddString(vector<string>& words) {
        if (words.empty()) {
            return "";
        }
        
        // For a particular character location, compute the difference
        // between char at that location and the preceeding location
        // for each of the words. Store the mapping between computed
        // diff and the word in a hash table. If diff is same across 
        // all words for the current character location, the hash table
        // will only have a single diff entry for this character location
        // with all words against the entry. If diff is different for
        // a particular word, it will appear a sole single word entry
        // against a particular diff; and all other words will be mapped
        // to a differnt common diff value
        int nWords = words.size();
        int wordLen = words[0].size();
        // Iterate over each char location
        for (int chrIdx = 1; chrIdx != wordLen; ++chrIdx) {
            unordered_map<int, vector<int> > diffToWordIdxTbl;
            // Compute the diff for each word at current char location
            // and store the diff value to word id mapping in hash table
            for (int wordIdx = 0; wordIdx != nWords; ++wordIdx) {
                auto & currWord = words[wordIdx];
                int diff = currWord[chrIdx] - currWord[chrIdx - 1];
                diffToWordIdxTbl[diff].emplace_back(wordIdx);
            }
            
            // Iterate over the hash table entries (hte) for
            // this character location
            for (auto & hte : diffToWordIdxTbl) {
                auto & wordsV = hte.second;
                if (1 == wordsV.size()) {
                    // Current diff entry has a lone word associated
                    // with it. Other diff entry has multiple words
                    // associated with it. This is the odd word
                    int oddWordIdx = wordsV[0];
                    return words[oddWordIdx];
                }
            }
        }
        
        return "";
    }
};
