// n => s.size()
// Time complexity : O(n)
// Space complexity : O(n) for unicode / O(1) for lowercase letter strings

class Solution {
public:
    bool
    isAnagram(string s, string t) {
        if (s.size() != t.size()) {
            // Error : Strings have to be of the same size
            return false;
        }
        
        if (s.empty() && t.empty()) {
            // Base case of both strings being empty
            return true;
        }

        //return isAnagramViaSorting(s, t);
        return isAnagramViaHashTable(s, t);
    }
    
private:
    
    bool
    isAnagramViaSorting(string& s, string& t) {
        // Sort two input strings in same order 
        // (either non-increasing or non-decreasing)
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());

        // Anagram strings are identical post sorting as they have same number
        // of identical chars and nothing else
        return s == t;
    }
    
    bool
    isAnagramViaHashTable(string& s, string& t) {
        // Two anagram strings are composed of same number of identical chars and
        // nothing else => respective frequency count tables should be identical

        // Two frequency count tables tracking letter frequency count of both strings
        // 's' & 't' can be reduced to a single frequency table as follows:-
        
        // Build a hash table which tracks the letter frequency of string 's' additively
        // and string 't' in subtractively. That is each letter from string 's' increments
        // frequency count of that letter; and each letter from string 't' decrements
        // frequency count of that letter of a single hash table.
        // Post-processing, all entries/letter frequency count of each letter
        // in the hash table should be zero if the strings are anagrams
        unordered_map<int, int> freqCntTbl;
        // Iterate over chars of both strings 's' & 't' in tandem
        for (auto i = 0; i != s.size(); ++i) {
            // string 's' chars contribute +vely to frequency count
            freqCntTbl[s[i]]++;
            // string 't' chars contribute -vely to frequency count
            freqCntTbl[t[i]]--;
        }
        
        // All entries in hash table should have zero occurrences for anagrams
        for (auto & ent : freqCntTbl) {
            if (ent.second != 0) {
                return false;
            }
        }
        return true;
    }
};
