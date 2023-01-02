class Solution {
public:
    bool
    detectCapitalUse(string word) {
        // Base case of single char word, anything allowed
        if (word.size() < 2) {
            return true;
        }
        
        // Check for presence of upper and lower case chars
        // in word from 2nd letter onwards
        bool uppercasePresent = false;
        bool lowercasePresent = false;
        for (int i = 1; i != word.size(); ++i) {
            auto & c = word[i];
            if (islower(c)) {
                lowercasePresent = true;
            } else {
                uppercasePresent = true;
            }
        }
        
        if (uppercasePresent && lowercasePresent) {
            // Both upper case and lower case from
            // 2 letter of word onwards not allowed
            return false;
        }
        
        if (uppercasePresent && islower(word[0])) {
            // First letter of word lowercase and upper case
            // from 2nd letter onwards not allowed
            return false;
        }
        
        return true;
    }
};
