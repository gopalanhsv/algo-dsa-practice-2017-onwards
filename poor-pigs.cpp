// Time complexity : O(log buckets)
// Space complexity : O(1)

class Solution {
public:
    int
    poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        // Maximum number of allowable test cycle iterations
        int nTestCycles = minutesToTest / minutesToDie;
        
        // Problem is equivalent to finding the minimum number of digits (i.e. minimum
        // number of pigs) required to encode all the numbers in a certain range (i.e.
        // entire set of buckets encoded as numerical ids [0, buckets - 1]); wherein each
        // digit encodes only a limited set of numbers (i.e. each digit belongs to the
        // closed range [0, numTestCycles])
        
        // Problem can be translated to information representation :-
        // If number of buckets is 'B', it represents a total of B states in the range
        // [0, B - 1] where any single bucket can be a poisoned bucket. Pigs form the
        // alphabet letters of a 'codeword' consisting of dead/alive state of the pigs
        // strung together
        // With T test cycles, a single pig can represent a total of
        // 'T + 1' states as follows
        // 1 -> pig dies after 1 feeding/test cycle
        // 2 -> pig dies after 2 feedings/test cycles
        // 3 -> pig dies after 3 feedings/test cycles
        // 4 -> pig dies after 4 feedings/test cycles
        // .....................................
        // r -> pig dies after r feedings/test cycles
        // .....................................
        // T -> pig dies after T feedings/last test cycles
        // 0 -> pig stays alive T feedings/last test cycles
        // The above implies that any pig by itself can be used to
        // check (T + 1) buckets in 'T' test cycles
               
        // So if there are 'p' pigs, the codeword consists of 'p'
        // letters where each letter can represent 'T + 1' states
        // So total number of possible codewords is (T + 1) ^ p
        // So 'p' pigs taken together can be used to represent 
        // a total of (T + 1) ^ p states at most.
        // Since any one of the 'B' buckets can be poisoned; we need
        // a total of 'B' states to be represented by 'p' pigs in
        // 'T' cycles s.t ((T + 1) ^ p) >= B
        int nMinPigs = 0;
        while (powl(nTestCycles + 1, nMinPigs) < buckets) {
            ++nMinPigs;
        }

        return nMinPigs;
    }
};
