// n => s.size()
// Time complexity : O(n)
// Space complexity : O(1)/O(26)
class Solution {
public:
    int
    minSteps(string s, string t) {
        if (s.size() != t.size()) {
            // Error : Both strings are not of the same size
            return -1; // Should be infinity ideally
        }
        
        // Two strings which are anagrams have identical occurence counts
        // for each of their constituent letters.

        // To make 't' an anagram of 's' => making the letter frequency count table of 't' to be 
        // identical to that of 's'. Letters in 't' which are not in 's'/have lesser occurence
        // count compared to that in 's' need to be deleted and replaced (one step each).
        // Minimum steps required to make 't' equal to 's' would be the sum of the differences
        // of occurence count of identical letters in 's' & 't'

        // Sum of difference of occurence counts of identical letters can be determined 
        // either by:-
        // (1) Building different frequency count tables for 's' & 't' and totalling up the
        // excess difference in frequency counts of letters in 't' compared to 's'; OR
        // (2) Using a single frequency count table with 's' letter counts being additively
        // maintained & 't' letter counts being subtractively maintained and adding up the
        // letter counts with -ve counts (these are the excess letters in 't' compared to 's'
        // which must be replaced)
        vector<int> freqCntTbl(26, 0);
        for (auto i = 0; i != s.size(); ++i) {
            // Increment occurence count for each letter in 's'
            freqCntTbl[int(s[i] - 'a')]++;
            // Decrement occurence count for each letter in 't'
            freqCntTbl[int(t[i] - 'a')]--;
        }
        
        // Add up the -ve differences in the occurence count table
        auto nSteps = 0;
        for (auto i = 0; i != 26; ++i) {
            if (freqCntTbl[i] < 0) {
                // Roundabout technique of getting absolute/magnitude of diffs for -ve nums
                nSteps -= freqCntTbl[i];
            }
        }
        return nSteps;
    }
};
