class TrieNode {
public:
    TrieNode() : _leaf(false) {}

    inline void
    setChildNode(char c, TrieNode* tn) {
        _childNodesTbl[c] = tn;
    }

    inline TrieNode*
    childNode(char c) {
        auto iter = _childNodesTbl.find(c);
        if (iter == _childNodesTbl.end()) {
            return nullptr;
        }
        return  iter->second;
        //return _childNodesTbl[c];
    }

    inline void
    setLeaf() {
        _leaf = true;
    }

    inline bool
    isLeafNode() {
        return _leaf;
    }

private:
    // Data members
    // Hash table marking the child trienodes for each of the
    // possible letters at current level
    unordered_map<char, TrieNode*> _childNodesTbl;
    // Marks the end of a word/leaf node
    bool _leaf;
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        _root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void
    insert(string word) {
        auto curr = _root;
        // Iterate through the word chars sequentially creating/adding
        // letters/trie nodes to the trie as required
        for (auto & c : word) {
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
    
    /** Returns if the word is in the trie. */
    bool
    search(string word) {
        auto curr = _root;
        // Iterate through the word chars sequentially
        for (auto & c : word) {
            // Check if current char is present in the trie
            // with the earlier occuring chars
            auto tn = curr->childNode(c);
            if (!tn) {
                return false;
            }
            curr = tn;
        }
        // Last char should be marked as a leaf node
        return (curr && curr->isLeafNode());
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool
    startsWith(string prefix) {
        auto curr = _root;
        // Iterate through the prefix chars sequentially
        for (auto & c : prefix) {
            // Each of the prefix chars should be present
            // in the trie as nodes as per occurrence order
            auto tn = curr->childNode(c);
            if (!tn) {
                return false;
            }
            curr = tn;
        }
        return curr != nullptr;
    }

private:

    // Data members
    TrieNode * _root; 
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
