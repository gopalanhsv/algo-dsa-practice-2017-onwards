// n => s.size()
// p => part.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    string
    removeOccurrences(string s, string part) {
        auto patternSz = part.size();
        auto patternLastChr = part[patternSz - 1];
        string outStr;
        int outStrSz = 0;
        for (auto & c : s) {
            if ((c == patternLastChr) && (outStrSz >= patternSz - 1)) {
                int nPatternChrsMatched = 1;
                while ((outStrSz > 0) && (nPatternChrsMatched < patternSz)) {
                    if (part[patternSz - nPatternChrsMatched - 1] == outStr[outStrSz - 1]) {
                        --outStrSz;
                        outStr.pop_back();
                        ++nPatternChrsMatched;
                    } else {
                        break;
                    }
                }

                if (nPatternChrsMatched != patternSz) {
                    while (nPatternChrsMatched > 0) {
                        outStr.push_back(part[patternSz - nPatternChrsMatched]);
                        ++outStrSz;
                        nPatternChrsMatched--;
                    }
                }
            } else {
                outStr.push_back(c);
                ++outStrSz;
            }
        }

        return outStr;
    }
};
