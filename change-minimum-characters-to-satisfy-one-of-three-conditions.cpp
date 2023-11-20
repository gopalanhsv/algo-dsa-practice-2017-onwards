// n = a.size(), m => b.size()
// Time complexity : O(max(m, n))
// Space complexity : O(m + n)

class Solution {
public:
    int minCharacters(string a, string b) {
        
        // Construct string 'a' character frequency count table
        vector<int> chrFreqCntTblA(26, 0);
        for (auto & c : a) {
            ++chrFreqCntTblA[c - 'a'];
        }
        
        // Construct string 'b' character frequency count table
        vector<int> chrFreqCntTblB(26, 0);
        for (auto & c : b) {
            ++chrFreqCntTblB[c - 'a'];
        }
        
        // Determine number of operations to make all chars in 'a' strictly less than 'b' OR
        // to make all chars in 'b' strictly less than 'a'
        auto minOps = minOpsForALessBOrBLessA(chrFreqCntTblA, chrFreqCntTblB);
        auto minOpsForOneLetter = minOpsForSameCharInAB(chrFreqCntTblB, chrFreqCntTblA, a.size(), b.size());
        
        return min(minOps, minOpsForOneLetter);
    }
    
private:
    
    int
    minOpsForALessBOrBLessA(vector<int>& chrFreqCntTblA, vector<int>& chrFreqCntTblB) {
        // Option #1 : Either all chars in A can be made strictly l.t. in B OR
        // Option #2 : Either all chars in B can be made strictly l.t. in A
        auto minOpsALessThanB = numeric_limits<int>::max();
        auto minOpsBLessThanA = numeric_limits<int>::max();
        for (auto partitionChr = 'a'; partitionChr < 'z'; ++partitionChr) {
            // String A < String B
            // All chars in A are made to be l.e 'partitionChr'
            // All chars in B are made to be g.t 'partitionChr'
            int nOpsALessB = 0;
            for (auto chrA = partitionChr + 1; chrA <= 'z'; ++chrA) {
                // All chars in A > 'partitionChr' are changed
                nOpsALessB += chrFreqCntTblA[chrA - 'a'];
            }
            for (auto chrB = 'a'; chrB <= partitionChr; ++chrB) {
                // All chars in B <= 'partitionChr' are changed
                nOpsALessB += chrFreqCntTblB[chrB - 'a'];
            }
            minOpsALessThanB = min(minOpsALessThanB, nOpsALessB);
            
            // String B < String A
            // All chars in B are made to be l.e 'partitionChr'
            // All chars in A are made to be g.t 'partitionChr'
            int nOpsBLessA = 0;
            for (auto chrB = partitionChr + 1; chrB <= 'z'; ++chrB) {
                // All chars in B > 'partitionChr' are changed
                nOpsBLessA += chrFreqCntTblB[chrB - 'a'];
            }
            for (auto chrA = 'a'; chrA <= partitionChr; ++chrA) {
                // All chars in A <= 'partitionChr' are changed
                nOpsBLessA += chrFreqCntTblA[chrA - 'a'];
            }
            minOpsBLessThanA = min(minOpsBLessThanA, nOpsBLessA);
        }
        return min(minOpsALessThanB, minOpsBLessThanA);
    }
    

    int
    minOpsForSameCharInAB(vector<int>& chrFreqCntTblA, vector<int>& chrFreqCntTblB, int lenA, int lenB) {
        int minOps = numeric_limits<int>::max();
        for (auto i = 0; i < 26; ++i) {
            // Num ops to make to make string 'a' consist only of char 'a' + i
            int nOpsForA = lenA - chrFreqCntTblA[i];
            // Num ops to make to make string 'b' consist only of char 'a' + i
            int nOpsForB = lenB - chrFreqCntTblB[i];
            // Update min operations to make 'a' & 'b' have same distinct char
            minOps = min(minOps, nOpsForA + nOpsForB);
        }
        return minOps;
    }
};
