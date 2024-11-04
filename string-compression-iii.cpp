// n => word.size();
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    string
    compressedString(string word) {
        
        // Iterate over the string characters sequentially from L->R
        // Perform run length encoding of the string with max run length of 9
        string compStr;
        auto wordSz = word.size();
        auto i = 0;
        while (i < wordSz) {
            // Run commences at current character with a run count of 1
            int runLen = 1;
            auto currChr = word[i++];
            // Compress at most 9 contiguous chars of same value in a single run
            while ((i < wordSz) && (runLen < 9) && (word[i] == currChr)) {
                ++i;
                ++runLen;
            }
            compStr += to_string(runLen);
            compStr.push_back(currChr);
            // Advance to next run
        }
        
        return compStr;
    }
};
