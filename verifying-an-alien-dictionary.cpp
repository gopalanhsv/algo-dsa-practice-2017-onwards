class Solution {
public:
    bool
    isAlienSorted(vector<string>& words, string order) {
        // Create a mapping from alien dictionary letters to
        // English letters (Using a vector and higher base for
        // faster lookup and less overhead)
        vector<char> alienToEnglishTbl('a' + 26);
        for (int i = 0; i != 26; ++i) {
            alienToEnglishTbl[order[i]] = 'a' + i;
        }
        
        // Convert all words in input string to their English equivalent
        // using the alien to english mapping table
        for (auto & word : words) {
            for (auto & c : word) {
                c = alienToEnglishTbl[c];
            }
        }
        
        // Iterate through the list of alien words converted to english
        // and check if adjacent words are in lexicographical order
        for (int i = 1; i != words.size(); ++i) {
            if (words[i] < words[i - 1]) {
                return false;
            }
        }
        return true;
    }
};
