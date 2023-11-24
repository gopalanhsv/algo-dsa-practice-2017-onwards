// Hash table approach
// n => num dictionary words, M => max dictionary word size, A => avg dictionary word size
// w => average word size of search words
// L => num search calls

// Space complexity : O(nA)
// Time complexity : O(L x A)/O(L x w)/O(L x M)

#define HASH_TABLE_APPROACH

#ifdef HASH_TABLE_APPROACH
class MagicDictionary {
public:
    MagicDictionary() { 
    }
    
    void
    buildDict(vector<string> dictionary) {
        // Insert each dictionary into the appropriate bucket as per word size
        for (auto & s : dictionary) {
            _lenToWordsTbl[s.size()].emplace_back(s);
        }
    }
    
    bool
    search(string searchWord) {
        // Lookup hash table and get the bucket with words of same length as
        // search word. Words of other length will require addition of a new
        // char along with mismatch handling (if any)
        auto wLen = searchWord.size();
        auto iter = _lenToWordsTbl.find(wLen);
        if (iter == _lenToWordsTbl.end()) {
            // Bucket with words of identical length not found
            // => dictionary string with single char mismatch not available
            return false;
        }
        // Iterate over each of the words in the dictionary of
        // identical length as search word
        auto & bucketWords = iter->second;
        for (auto & word : bucketWords) {
            if (singleCharMismatch(searchWord, word)) {
                // Current dictionary word has a single char mismatch with search word
                // => dictionary word can be obtained from search word with single change
                return true;
            }
        }
        // No word in dictionary available with single char mismatch from search word
        return false;
    }
    
private:
    
    bool
    singleCharMismatch(string& s1, string& s2) {
        // Return true if there only a single char mismatch between
        // words s1 & s2, false otherwise
        int misMatchCnt = 0;
        auto wLen = s1.size();
        for (auto i = 0; i != wLen; ++i) {
            if (s1[i] != s2[i]) {
                if (++misMatchCnt > 1) {
                    break;
                }
            }
        }
        return misMatchCnt == 1;
    }
    
    // Data members
    // Hash table mapping dictionary words lengths to the
    // bucket of words with that length
    unordered_map<int, vector<string> > _lenToWordsTbl;
};
#endif

#ifdef TRIE_APPROACH
class MagicDictionary {
public:
    MagicDictionary() {
        
    }
    
    void buildDict(vector<string> dictionary) {
        
    }
    
    bool search(string searchWord) {
        
    }
};
#endif

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
