// n => dictionary.size(), M => max len of word in dictionary, T => s.size()

// Approach 1
// Time complexity : O(n x max(M, T))
// Space complexity : O(1)

// Approach 2
// Time complexity : O(Mnlogn + n x max(M, T))
// Space complexity : O(logn)

class Solution {
public:
    string
    findLongestWord(string s, vector<string>& dictionary) {
        return findLongestWordApproach1(s, dictionary);
        //return findLongestWordApproach2(s, dictionary);
    }

private:
    
    bool
    isSubsequence(string& w1, string& w2) {
        // Returns 'true' if string 'w1' is a subsequence of
        // the string 'w2', 'false' otherwise
        auto w1SubStrLen = 0;
        auto w2Idx = 0;
        // Iterate over each char of 'w1' from L->R sequentially
        for (auto & c : w1) {
            // Find first occurence of current char in substring w2[w2Idx, ...]
            // which is yet to to be examined for chars of w1
            w2Idx = w2.find(c, w2Idx);
            if (w2Idx == string::npos) {
                // No occurence of current char => w1 cannot be a subsequence of w2
                break;
            }
            // Advance search region in supersequence 'w2' to 1 char beyond
            // the latest index which matched with 'w1'
            ++w2Idx;
            ++w1SubStrLen;
        }
        return w1SubStrLen == w1.size();
    }
    
    string
    findLongestWordApproach1(string& s, vector<string>& dictionary) {
        string longestWd;
        int longestWdLen = 0;
        auto seqWdLen = s.size();
        // Iterate over each word in dictionary
        for (auto & dictWd : dictionary) {
            auto wLen = dictWd.size();
            if ((wLen <= seqWdLen) && isSubsequence(dictWd, s)) {
                // Current dictionary word is a subsequence of string 's'
                if (wLen > longestWdLen) {
                    // Update the longest dictionary word
                    longestWdLen = wLen;
                    longestWd = dictWd;
                } else if (wLen == longestWdLen) {
                    // Update the longest dictionary word to lexicographically the smallest one
                    longestWd = min(longestWd, dictWd);
                }
            }
        }
        
        return longestWd;
    }
    
    string
    findLongestWordApproach2(string& s, vector<string>& dictionary) {
        
        // Sort the dictionary words in the descending order of their lengths
        // with the same length words being sorted in lexicographical order
        sort(dictionary.begin(), dictionary.end(),
            [&](const auto & s1, const auto & s2) {
                if (s1.size() == s2.size()) {
                    return s1 < s2;
                }
                return s1.size() > s2.size();
            });
        
        string longestWd;
        // Iterate over each word in dictionary
        for (auto & dictWd : dictionary) {
            auto wLen = dictWd.size();
            if (isSubsequence(dictWd, s)) {
                // Current dictionary word is a subsequence of string 's'
                // and is the longest word which is lexicograohically the
                // smallest
                longestWd = dictWd;
                break;
            }
        }
        
        return longestWd;
    }
};
