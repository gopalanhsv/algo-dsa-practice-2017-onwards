// n => words.size()
// P => pref.size()
// Time Complexity : O(nP)
// Space Complexity : O(1)

class Solution {
public:
    int
    prefixCount(vector<string>& words, string pref) {
        auto prefixLen = pref.size();
        auto count = 0;
        // Iterate over each word in words
        for (auto & w : words) {
            // Check if the word has given prefix and increment count if affirmative
            if ((w.size() >= prefixLen) &&
                 equal(w.begin(), w.begin() + prefixLen, pref.begin()) ) { 
                ++count;
            }
        }
        
        return count;
    }
};
