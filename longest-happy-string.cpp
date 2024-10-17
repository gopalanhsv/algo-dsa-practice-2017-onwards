// Time Complexity : O(a + b + c) / O(n)
// Space Complexity : O(1)

class Solution {
public:
    string
    longestDiverseString(int a, int b, int c) {
        typedef struct _ChrFreqInfoT {
            string chr;
            int freq;
            _ChrFreqInfoT(string c, int f) : chr(c), freq(f) {}
        } ChrFreqInfoT;
        
        struct ChrFreqInfoCmpObj {
            bool
            operator()(const ChrFreqInfoT & cfi1, const ChrFreqInfoT & cfi2) {
                return cfi1.freq < cfi2.freq;
            }
        };
        
        priority_queue<ChrFreqInfoT, vector<ChrFreqInfoT>, ChrFreqInfoCmpObj> maxHeap;
        if (a) {
            ChrFreqInfoT cfi("a", a);
            maxHeap.push(cfi);
        }
        if (b) {
            ChrFreqInfoT cfi("b", b);
            maxHeap.push(cfi);
        }
        if (c) {
            ChrFreqInfoT cfi("c", c);
            maxHeap.push(cfi);
        }
        
        string longestStr;
        string prevAddedChr;
        while (maxHeap.size() > 1) {
            auto maxCfi = maxHeap.top();
            maxHeap.pop();

            longestStr += maxCfi.chr;
            --maxCfi.freq;
            if ((maxCfi.freq >= 1) && (prevAddedChr != maxCfi.chr)) {
                longestStr += maxCfi.chr;
                --maxCfi.freq;
            }
            
            auto secondMaxCfi = maxHeap.top();
            maxHeap.pop();
            longestStr += secondMaxCfi.chr;
            --secondMaxCfi.freq;
            prevAddedChr = secondMaxCfi.chr;
            
            if (maxCfi.freq > 0) {
                maxHeap.push(maxCfi);
            }
            if (secondMaxCfi.freq > 0) {
                maxHeap.push(secondMaxCfi);
            }
        }
        
        if (!maxHeap.empty()) {
            auto maxCfi = maxHeap.top();
            maxHeap.pop();
            auto lStrSz = longestStr.size();
            auto chrToBeAdded = maxCfi.chr;
            auto nCharsAvl = maxCfi.freq;
            if (lStrSz >= 2) {
                if (chrToBeAdded[0] == longestStr[lStrSz - 1]) {
                    if (chrToBeAdded[0] == longestStr[lStrSz - 2]) {
                        return longestStr;
                    }
                    return longestStr + chrToBeAdded;
                }
            } else if (lStrSz > 0) {
                if (chrToBeAdded == prevAddedChr) {
                    return longestStr + chrToBeAdded;
                }
            }
            
            longestStr += chrToBeAdded;
            if (nCharsAvl > 1) {
                longestStr += chrToBeAdded;
            }
        }

        return longestStr;
    }
};
