// n => s.size()
// Time complexity : O(n)
// Space complexity : O(1)
class Solution {
public:
    bool
    halvesAreAlike(string s) {
        
        // Count the number of vowels in first half of string
        auto strSz = s.size();
        auto halfStrSz = strSz / 2;
        auto nVowels = 0;
        for (auto i = 0; i < halfStrSz; ++i) {
            if (isVowel(s[i])) {
                ++nVowels;
            }
        }
        
        // Reduce number of vowels found in first half by the
        // number of vowels in second half of string
        for (auto i = halfStrSz; i < strSz; ++i) {
            if (isVowel(s[i])) {
                --nVowels;
            }
        }
        
        // Number of vowels after count and reduction should be nil
        return (0 == nVowels);
    }
    
private:
    
    inline bool
    isVowel(char c) {
        return
            (c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u') ||
            (c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U');
    }
};
