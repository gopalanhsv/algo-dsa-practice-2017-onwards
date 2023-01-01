class Solution {
public:
    typedef string::size_type strSzT; 
    
    bool
    wordPattern(string pattern, string s) {
    
        // Hash table for maintaining mapping from a letter in the pattern to
        // a word in the string; and another table for reverse mapping
        unordered_map<char, string> letterToStringTbl;
        unordered_map<string, char> stringToLetterTbl;
        
        strSzT patternLetterIdx = 0;
        strSzT i = 0;
        while ((i < s.size()) &&
               (patternLetterIdx < pattern.size())) {
            
            // Find the first word in string 's' positioned at/after index 'i'
            string word;
            strSzT j = findWord(s, i, word);
            
            // Current pattern letter
            char patternLetter = pattern[patternLetterIdx];
            
            // Map the current pattern letter to the current word if a mapping
            // doesn't exist; and update the mappings. If a mapping exists for
            // either the current word or current pattern letter, check the current
            // word and pattern are consistent with earlier created mappings
            auto it1 = letterToStringTbl.find(patternLetter);
            if ((it1 != letterToStringTbl.end()) && (it1->second != word)) {
                return false;
            }
            auto it2 = stringToLetterTbl.find(word);
            if ((it2 != stringToLetterTbl.end()) && (it2->second != patternLetter)) {
                return false;
            }
            
            // New mapping, update the mapping tables
            letterToStringTbl[patternLetter] = word;
            stringToLetterTbl[word] = patternLetter;
            
            // Advance to next word in string and next pattern letter in pattern
            i = j;
            ++patternLetterIdx;
        }
        
        // Both pattern and string should have been fully explored
        return ((i == s.size()) && 
                (patternLetterIdx == pattern.size()));
    }
    
private:
    
    strSzT
    findWord(string & s, string::size_type i, string & word) {
        // Beginning of word at 'i'
        while (isspace(s[i])) {
            ++i;
        }
        
        // Ending of word at j
        strSzT j = i + 1;
        while (j < s.size() && !isspace(s[j])) {
            ++j;
        }
        
        word = s.substr(i, j - i);
        
        return j;
    }
};
