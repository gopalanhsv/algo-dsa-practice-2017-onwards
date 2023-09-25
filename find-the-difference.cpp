// p => s.size(), q => t.size()
// XOR Approach
// Time complexity : O(max(p, q))
// Space complexity : O(1)

// Hash Table Approach
// Time complexity : O(max(p, q))
// Space complexity : O(26) = O(1)
class Solution {
public:
    char
    findTheDifference(string s, string t) {
        // Base case of empty string s
        if (s.empty()) {
            return t[0];
        }
      
        //return findTheDifferenceHashTableApproach(s, t);
        return findTheDifferenceXorApproach(s, t);
    }
    
private:
    
    char
    findTheDifferenceXorApproach(string s, string t) {
        // XOR all chars of 's' & 't'
        char allElemsXor = 0;
        for (auto & c : s) {
            allElemsXor ^= c;
        }
        for (auto & c : t) {
            allElemsXor ^= c;
        }
        // Identical chars between 's' & 't' cancel out leaving the extra char added to 't'
        return allElemsXor;
    }
    
    char
    findTheDifferenceHashTableApproach(string s, string t) {
        // Build frequency count table of all chars in 't'
        unordered_map<char, int> tCharsFreqCntTbl;
        for (auto & c : t) {
            tCharsFreqCntTbl[c]++;
        }
        
        // Iterate over each of 's' chars. 
        unordered_multiset<char>::iterator iter;
        for (auto & c : s) {
            // Remove char seen in 's' from the 't' char table (adjust freq cnt)
            if (--tCharsFreqCntTbl[c] == 0) {
                tCharsFreqCntTbl.erase(c);
            }
        }
        
        // Sole remaining entry key in 't' hash table would be the extra character
        char extraChar = (tCharsFreqCntTbl.begin())->first;
        return extraChar;
    }

};
