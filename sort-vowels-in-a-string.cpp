// s = s.size()
// Time complexity : O(n) as O(nlog10) => O(1)
// Space complexity : O(1)
class Solution {
public:
    string
    sortVowels(string s) {
        string vowels("aeiouAEIOU");
        unordered_set<char> vowelSet(vowels.begin(), vowels.end());
        
        // Build frequency count table mapping vowels chars in string
        // 's' to respective occurrence count. Frequency count table is
        // arranged/sorted in nondecreasing order of vowels char ascii values 
        map<char, int> charToFreqCntTbl;
        for (auto & c : s) {
            if (vowelSet.find(c) != vowelSet.end()) {
                // Current char is a vowel
                charToFreqCntTbl[c]++;
            }
        }
        
        // Use the sorted vowel frequency count table to restructure
        // string 's' s.t. vowel chars in 's' get sorted
        auto freqTblIter = charToFreqCntTbl.begin();
        for (auto & c : s) {
            if (vowelSet.find(c) != vowelSet.end()) {
                // Current char is a vowel
                // Replace with replacement vowel char
                auto sortedReplacementChr = freqTblIter->first;
                c = sortedReplacementChr;
                // Decrement occurence count of replacement char to account for its usage 
                if (--(freqTblIter->second) == 0) {
                    // All occurences of replacement cchar used up => move to next
                    if (++freqTblIter == charToFreqCntTbl.end()) {
                        break;
                    }
                }
            }
        }
        
        return s;
    }
};
