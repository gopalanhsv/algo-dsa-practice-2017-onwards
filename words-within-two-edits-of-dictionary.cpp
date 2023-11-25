// q => qeries.size(), d => dictionary.size(), L => word length (query and dict)
// Time complexity : O(qdL)
// Space complexity : O(1)

class Solution {
public:
    vector<string>
    twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        return twoEditWordsViaHammingDistance(queries, dictionary);
    }
    
private:
    
    inline int
    hammingDistance(const string& s1, const string& s2) {
        // Count the number of mismatched chars at identical positions
        // between the two strings
        auto hd = 0;
        auto strSz = s1.size();
        for (auto i = 0; i != strSz; ++i) {
            if (s1[i] != s2[i]) {
                ++hd;
            }
        }
        return hd;
    }
    
    vector<string>
    twoEditWordsViaHammingDistance(vector<string>& queries, vector<string>& dictionary) {
        vector<string> outV;
        // Iterate over each query word
        for (auto & queryStr : queries) {
            // For the current query word, check if any word in the dictionary
            // can be reached within 2 edits (i.e at a hamming distance of 2)
            for (auto & dictStr : dictionary) {
                if (hammingDistance(queryStr, dictStr) <= 2) {
                    // 'dictStr' is obtainable from 'queryStr' within 2 edits
                    outV.emplace_back(queryStr);
                    // Move on to next qquey
                    break;
                }
            }
        }
        
        return outV;
    }
};
