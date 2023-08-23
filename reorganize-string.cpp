// n => s.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)
class Solution {
public:
    string
    reorganizeString(string s) {
        // Build char frequency count table for the string
        unordered_map<char, int> chrFreqTbl;
        for (auto & c : s) {
            chrFreqTbl[c]++;
        }
        
        // Insert all the (character, frequency count) into a priority queue (max heap) wherein
        // a higher frequency elem are placed near heap top compared to a lower frequency elem
        typedef pair<char, int> ElemFreqCntPairT;
        struct ElemFreqCntPairCmpObj {
            bool
            operator()(const ElemFreqCntPairT & efp1,
                       const ElemFreqCntPairT & efp2) {
                return efp1.second < efp2.second;
            }
        };
        priority_queue<ElemFreqCntPairT, vector<ElemFreqCntPairT>, ElemFreqCntPairCmpObj> maxHeap;
        
        // Insert all elements from hash table to the priority queue
        for (auto & hte : chrFreqTbl) {
            // hte => hash table entry
            ElemFreqCntPairT efp;
            efp.first = hte.first;
            efp.second = hte.second;
            maxHeap.push(efp);
        }

        // Adopt the following greedy approach to build the reorganized string:-
        // 1. Clear original string
        // 2. Select char with highest frequency count from amongst the remaining chars. Commencing
        //    from the lowest available free index, place each instance of the char at successive
        //    alternate locations (leaving a single space in between -- i.e even locations),
        //    decrementing the frequencycount at each step till it drops to 0. If the end of string
        //    is hit, wrap around and start filling again in the odd locations in sequence
        // 3. Repeat step 2 till all chars from most frequent to least frequent are successfully placed
        int strIdx = 0;
        string rs(s.size(), '1');
        while (!maxHeap.empty()) {
            // Select (char, frequency cnt) tuples with max frequency
            auto efp = maxHeap.top();
            maxHeap.pop();

            // Fill in each instance of the current char as per frequency count
            // with a gap of 1 space/char between successive chars
            for (int i = 0; i < efp.second; ++i) {

                rs[strIdx] = efp.first;
                if ((strIdx != 0) && (rs[strIdx] == rs[strIdx - 1])) {
                    // Adjacent chars are same, Rearrangement not possible
                    return "";
                }
                
                // Compute next write location in rearranged string
                strIdx += 2;
                if (strIdx >= rs.size()) {
                    // Rollover
                    strIdx = 1;
                }
            }
        }
        
        return rs;
    }
};
