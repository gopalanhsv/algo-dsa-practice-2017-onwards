class Solution {
public:
    bool
    isIsomorphic(string s, string t) {
        // Strings of unequal size
        if (s.size() != t.size()) {
            return false;
        }
        
        // Iterate through both strings in lockstep char by char
        // and construct a mapping table between chars in string s
        // to chars in string t; which is tracking the conversion.
        // If at any point an inconsistency is hit in the mapping
        // conversion, isomorphism of s & t stops at that character
        // NOTE :- MAPPING to be maintained and checked in both directions
        unordered_map<char, char> strSToStrTTbl;
        unordered_map<char, char> strTToStrSTbl;
        unordered_map<char, char>::iterator iter;
        for (int i = 0; i != s.size(); ++i) {
            auto & sChar = s[i];
            auto & tChar = t[i];
            iter = strSToStrTTbl.find(sChar);
            if (iter != strSToStrTTbl.end()) {
                // Earlier mapping from current sChar to some tChar exists
                if (iter->second != tChar) {
                    // Current new mapping inconsistent with earlier
                    return false;
                }
            } else {
                // No earlier mapping from current sChar to some tChar.
                // Create a new one
                strSToStrTTbl[sChar] = tChar;
            }

            iter = strTToStrSTbl.find(tChar);
            if (iter != strTToStrSTbl.end()) {
                // Earlier mapping from current tChar to some sChar exists
                if (iter->second != sChar) {
                    // Current new mapping inconsistent with earlier
                    return false;
                }
            } else {
                // No earlier mapping from current tChar to some sChar.
                // Create a new one
                strTToStrSTbl[tChar] = sChar;
            }
            
        }
        // All chars have consistent mapping
        return true;
    }
};
