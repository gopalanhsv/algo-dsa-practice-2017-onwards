// m => s.size(), n => t.size()
// Time complexity : O(n + m)
// Space complexity : O(1)/O(26)

class Solution {
public:
    int
    minSteps(string s, string t) {
        
        // Two strings which are anagrams have identical occurence counts
        // for each of their constituent letters.
        
        // To make 't' an anagram of 's' => making the letter frequency count
        // table of 't' to be identical to that of 's'.
        // Min number of steps reduces to adding up the differences in
        // ocurrence counts of identical letters between 's' & 't'.
        // Letters in 't' which are not in 's'/have lesser occurence
        // count compared to that in 's' need to be deleted and replaced (one step each).
        // Minimum steps required to make 't' equal to 's' would be the sum of the differences
        // of occurence count of identical letters in 's' & 't'
        
        // Sum of difference of occurence counts of identical letters can be determined by
        // building different frequency count tables for 's' & 't' and adding up the
        // absolute difference in frequency counts of letters in 't' compared to 's';
        // OR by using a single frequency count table with 's' letter counts
        // being additively maintained & 't' letter counts being subtractively maintained
        // and adding up the absolute value of differences between (these are the extra
        // letters which need to be added to 's' & 't')
        vector<int> diffFreqCntTbl(26, 0);
        // Increment occurence count for each letter in 's'
        for (auto & c : s) {
            diffFreqCntTbl[int(c - 'a')]++;
        }
        // Decrement occurence count for each letter in 't'
        for (auto & c : t) {
            diffFreqCntTbl[int(c - 'a')]--;
        }
        
        // Add up the differences in the occurence count table
        auto nSteps = 0;
        for (auto i = 0; i != 26; ++i) {
            nSteps += abs(diffFreqCntTbl[i]);
        }
        return nSteps;
    }
};
