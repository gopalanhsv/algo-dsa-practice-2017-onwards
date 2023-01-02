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
        
        if (uppercasePresent) {
            if (lowercasePresent || islower(word[0])) {
                // Either 2nd letter onwards is an upper + lowercase mix OR
                // 1st letter is lowercase with 2nd letter onwards having
                // some uppercase letters
                return false;
            }
        }

        return true;
    }
};
