// n => words.size(), A => average length of dictionary words, M => max dictionary word length
// Time complexity : O(nM)
// Space complexity : O(nA)

// This problem is identical to LC720
// https://leetcode.com/problems/longest-word-in-dictionary/ 
// Alternative approach of solving the problem using hash table
// (with/without sorting) is found there in personal/github listing

class TrieNode {
public:
    TrieNode() {
        // Initialize
        // 26 chars for each lowercase letter
        _childNodesTbl.resize(26);
        _isLeaf = false;
    }
    
    inline void
    setChildNode(char c, TrieNode* tn) {
        _childNodesTbl[c - 'a'] = tn;
    }
    
    inline void
    setLeaf() {
        _isLeaf = true;
    }
    
    inline TrieNode*
    childNode(char c) {
        return _childNodesTbl[c - 'a'];
    }
    
    bool
    isLeaf() {
        return _isLeaf;
    }
    
private:
    
    // Data members
    // Hash table maintaining the child trienodes for each of the
    // possible letters at current level
    vector<TrieNode*> _childNodesTbl;
    // Marks the end of a word/leaf node
    bool _isLeaf;
};

class Trie {
public:
    Trie() : _root(nullptr) {
        _root = new TrieNode();
    }
    
    void
    insertWord(string& w) {
        auto curr = _root;
        // Iterate through the word chars sequentially creating trie nodes
        // for each char; and adding them against the appropriate letter/char in
        // the respective parent trie node
        for (auto & c : w) {
            auto tn = curr->childNode(c);
            if (!tn) {
                tn = new TrieNode();
                curr->setChildNode(c, tn);
            }
            curr = tn;
            
        }
        // Mark the end of the word
        curr->setLeaf();
    }
    
    bool
    wordExistsWithAllWordPrefixes(string & w) {
        auto curr = _root;
        // Iterate through the word chars sequentially
        for (auto & c : w) {
            // Check if current char is present in the trie after appropriate
            // prefix chars; with a word ending at current char
            auto tn = curr->childNode(c);
            if (!tn || !tn->isLeaf()) {
                return false;
            }
            curr = tn;
        }
        return true;
    }
    
private:
    
    // Data members
    TrieNode *_root;
};

class Solution {
public:
    string
    longestWord(vector<string>& words) {
        
        // Create a trie and insert all dictionary words into the trie
        Trie trie;
        for (auto & word : words) {
            trie.insertWord(word);
        }
        
        // Iterate through each word in teh dictionary
        string longestMatchSeen;
        auto longestMatchLenSeen = 0;
        for (auto & word : words) {
            auto wLen = word.size();
            if (wLen >= longestMatchLenSeen) {
                // Check for existence of current word and all its prefixes
                // in the trie
                if (trie.wordExistsWithAllWordPrefixes(word)) {
                    // Update the maximal length word which is present in trie
                    // with all its prefixes
                    if (wLen > longestMatchLenSeen) {
                        longestMatchLenSeen = wLen;
                        longestMatchSeen = word;
                    } else {
                        // For multiple words of maximal length, prefer lexicographically
                        // the smallest word
                        longestMatchSeen = min(longestMatchSeen, word);
                    }
                }
            }
        }
        
        return longestMatchSeen;
    }
};
