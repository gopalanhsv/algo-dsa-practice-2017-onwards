// Time complexity : O(s.size()) / O(n)
// Space complexity : O(s.size()) / O(n)
class Solution {
public:
    bool
    buddyStrings(string s, string goal) {
        if ((s.size() != goal.size()) || s.empty()) {
            // Base case of unequal sized strings/empty string
            return false;
        }
        
        // Two possibilities :-
        // 1. Two strings are same - there should be at least 1 duplicate
        // character in the string which can be swapped 
        // 2. Two strings are different - the strings should differ at
        // exactly two locations s.t. the swapping chars at mismatch locations
        // should make both strings equal
        int goalSz = goal.size();
        vector<pair<char, char> > misMatchCharsV;
        unordered_set<char> goalStrChrTbl;
        for (int i = 0; i < goalSz; ++i) {
            auto & sChr = s[i];
            auto & gChr = goal[i];
            if (sChr != gChr) {
                // Mismatch occurrence - store mismatch chars to check if swap possible
                if (misMatchCharsV.size() > 2) {
                    // More tna 2 mismatches between the two string => single swap fails
                    return false;
                }
                misMatchCharsV.push_back({sChr, gChr});
            } else {
                // Identical chars, insert in hash table
                goalStrChrTbl.insert(sChr);
            }
        }
        
        if (misMatchCharsV.empty()) {
            // Both strings identical, Check if string has at least 1 duplicate char
            return goalStrChrTbl.size() < goal.size();  
        }
        
        if (misMatchCharsV.size() != 2) {
            // mismatch between the two string is not 2 => single swap fails
            return false;
        }
        
        // 2 mismatches, check if mismatch chars can be swapped to correct mismatch
        auto & firstMismatch = misMatchCharsV[0];
        auto & secondMismatch = misMatchCharsV[1];
        return (firstMismatch.first == secondMismatch.second &&
                firstMismatch.second == secondMismatch.first);
        
    }
};
