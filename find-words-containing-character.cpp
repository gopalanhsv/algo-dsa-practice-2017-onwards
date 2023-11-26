// n => words.size(), L => average word length in of strings in 'words'
// Time complexity : O(nL)
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    findWordsContaining(vector<string>& words, char x) {
        vector<int> outV;
        auto nWords = words.size();
        for (auto idx = 0; idx != nWords; ++idx) {
            auto & word = words[idx];
            if (word.find(x) != string::npos) {
                outV.emplace_back(idx);
            }
        }
        return outV;
    }
};
