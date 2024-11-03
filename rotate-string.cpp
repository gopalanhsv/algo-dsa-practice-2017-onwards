// m => s.size(), n => goal.size()
//
// Both Approaches:
// Time Complexity : O(n)
// Space Complexity : O(n)

class Solution {
public:
    bool
    rotateString(string s, string goal) {
        if (s.size() != goal.size()) {
            return false;
        }
        
        if (s.size() == 1) {
            return true;
        }
    
        return rotateStringSmart(s, goal);
        //return rotateStringBySplit(s, goal);
    }
    
    
private:
    
    bool
    rotateStringBySplit(string &s, string& goal) {
        auto strSz = s.size();
        auto goalSz = goal.size();
        
        // First character of string
        char strFirstChar = s[0];
        // First occurrence in goal where the first char of string occurs
        // Possible start of rotated string
        auto posInGoal = goal.find(strFirstChar, 0);
        while (posInGoal != string::npos) {
            // Check if reversal of rotation leads to the original string (assuming that
            // the current location of first char of string is the actual location of first char) 
            if (goal.substr(posInGoal) + goal.substr(0, posInGoal) == s) {
                // Unrotated goal string matches original string
                return true;
            }
            
            // Advance to next occurrence of first char of 'string' in goal
            posInGoal = goal.find(strFirstChar, posInGoal + 1);
        }
        
        return false;        
    }
    
    bool
    rotateStringSmart(string& s, string& goal) {
        // Concatenate 2 instances of 'goal'. If 'goal' is a rotation of 's',
        // the 's' will have an occurrence in the concatenated instance
        return (goal + goal).find(s) != string::npos;
    }
};
