// Space complexity : O(dictionary.size())

// Constructor
// Time complexity : O(dictionary.size())
// inUnique()
// Time complexity : O(1)

class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string>& dictionary) {
        // Iterate over each word in the dictionary
        for (auto & w : dictionary) {
            // Add current word and its abbreviation to internal state tables
            _wordsTbl.insert(w);
            _abbrToFreqCntTbl[computeAbbreviation(w)]++;
        }
    }
    
    bool
    isUnique(string word) {
        // Abbreviation of input word
        string abbrStr = computeAbbreviation(word);
        // Lookup abbreviated string in dictionary
        auto it = _abbrToFreqCntTbl.find(abbrStr);
        if (it == _abbrToFreqCntTbl.end()) {
            // Abbreviation not found => word is unique
            return true;
        }
        
        // Word abbreviation found
        
        if (word.size() > 2) {
            // Word is abbreviated
            // => Word is unique only if single instance of abbreviation seen in
            // word dictionary along with given word
            return ((it->second == 1) && (_wordsTbl.find(word) != _wordsTbl.end()));
        } 
        
        // Word cannot be abbreviated
        // => Word is unique only if seen in word dictionary
        return (_wordsTbl.find(word) != _wordsTbl.end());
    }
    
private:

    string
    computeAbbreviation(string& w) {
        auto wSz = w.size();
        if (wSz <= 2) {
            return w;
        }
        
        // Num letters between 1 and last char of word
        auto nInBetweenLetters = wSz - 2;
        // Abbreviation of input word is the concatenation of first and last letter
        // with the count of letters in between
        return string(1, w[0]) + to_string(nInBetweenLetters) + string(1, w[wSz - 1]);
    }
    
    // Data members
    // Hash table mapping word abbreviations to the count of words
    // having respective abbreviations from the input dictionary
    unordered_map<string, int> _abbrToFreqCntTbl;
    // Hash table of words from the input dictionary
    unordered_set<string> _wordsTbl;
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */
