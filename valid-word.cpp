// n => word.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    bool
    isValid(string word) {
        if (word.size() < 3) {
            return false;
        }

        // Iterate over each word char
        bool hasConsonant = false;
        bool hasVowel = false;
        for (auto & c : word) {
            if (!isdigit(c) && !isalpha(c)) {
                // All chars should be either digits or alphabets
                return false;
            }

            if ('a' == c || 'e' == c || 'i' == c || 'o' == c || 'u' == c ||
                'A' == c || 'E' == c || 'I' == c || 'O' == c || 'U' == c) {
                hasVowel = true;
            } else if (isalpha(c)) {
                hasConsonant = true;
            } 
        }
        
        return (hasConsonant && hasVowel);
    }
};
