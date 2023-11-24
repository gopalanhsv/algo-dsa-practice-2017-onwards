// n => words.size(), M => maximum word len in words

// Sorting + Hashing Approach
// Time complexity : O(nlogn + nM)
// Space complexity : O(logn + nM)

// This problem is identical to LC1858
// https://leetcode.com/problems/longest-word-with-all-prefixes/ 
// Alternative approaches of solving the problem using a trie
// is found there in personal/github listing

class Solution {
public:
    string
    longestWord(vector<string>& words) {
        if (words.empty()) {
            return "";
        }
        
        return longestWordViaSortingAndHashing(words);
    }

private:
    
    string
    longestWordViaSortingAndHashing(vector<string>& words) {
        // Sort the words in the ascending order of their size
        // For words of identical size sort the words lexicographically
        // Sorting ensures any word w1 which comes later in the array should have all
        // its respective word prefixes (of size 1, 2, 3, ... w1.size() - 1 letters)
        // present/seen earlier in the array; if w1 is to built one character at a time
        sort(words.begin(), words.end(),
            [&](const auto & w1, const auto & w2) {
                if (w1.size() == w2.size()) {
                    return w1 < w2;
                }
                return w1.size() < w2.size();
            });
        
        // Hash table of words seen so far (only valid word prefixes which could be
        // built using one char at a time)
        unordered_set<string> seenPrefixesTbl;
        string longestWdSeen;
        int longestWdLen = 0;
        // Add all single char words to hash table (these dont require any prefixes)
        auto wIdx = 0;
        for (auto & word : words) {
            auto wLen = word.size();
            if (wLen > 1) {
                // Prefix of current 'word' should have seen earlier if 
                // it has to be built one char at a time
                auto prefix = word.substr(0, wLen - 1);
                if (seenPrefixesTbl.find(prefix) == seenPrefixesTbl.end()) {
                    // Current word cannot be built upon earlier seen words
                    // Skip and proceed to next word
                    continue;
                }
            }
            // Single char words added by default
            
            // Current word can be built one char at a time, Add it to prefixes table
            // so that larger words having this prefix can use it
            seenPrefixesTbl.insert(word);
            // Update the longest word which can be built
            if (wLen > longestWdLen) {
                longestWdLen = wLen;
                longestWdSeen = word;
            }
        }
        
        return longestWdSeen;
    }
};
