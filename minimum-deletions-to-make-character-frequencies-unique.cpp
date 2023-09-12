// n => s.size()
// Time complexity : O(n) + O(26log26)
// Space complexity : O(n)

class Solution {
public:
    int
    minDeletions(string s) {
        // Build the character frequency table for the string
        vector<int> chrFreqTbl(26, 0);
        for (auto c : s) {
            chrFreqTbl[c - 'a']++;
        }
        
        // Good string => each character has a unique frequency
        // One can only delete a char, not add. To make the string good with the minimum
        // number of deletions; adopt the following greedy approach:-

        // Amongst the remaining unprocessed chars at each step, ensure that char with max
        // frequency is reduced by the minimum amount possible s.t. its new frequency count
        // is not identical with the frequency count of chars already processed. For execing
        // this step, sort the string char frequencies in non-decreasing order
        vector<int> strChrFreqV;
        for (int i = 0; i < 26; ++i) {
            auto freq = chrFreqTbl[i];
            if (freq > 0) {
                strChrFreqV.emplace_back(freq);
            }
        }
        sort(strChrFreqV.begin(), strChrFreqV.end());
        
        auto minDeletions = 0;
        // One of the chars with max frequency retains its frequency (no deletions)
        auto maxFreq = strChrFreqV.back();
        // Next char must have a frequency at least one less
        int maxAllowedFreqForNextChr = maxFreq - 1;
        // Iterate over the unprocessed chars in the descending order of frequencies
        for (int i = strChrFreqV.size() - 2; i >= 0; --i) {
            // Frequency of current char (char with max frequency amongst unprocessed chars)
            // prior to deletion
            int currChrFreq = strChrFreqV[i];
            if (currChrFreq > maxAllowedFreqForNextChr) {
                // Deletions need to be applied to current char to bring its occurence
                // count it to the max allowable frequency
                minDeletions += (currChrFreq - maxAllowedFreqForNextChr);
                // Update max allowable frequency for next char with identical
                // or lesser frequency compared to current char
                maxAllowedFreqForNextChr = max(maxAllowedFreqForNextChr - 1, 0);
            } else {
                // Deletions no required 
                // Update max allowable frequency for next char with identical
                // or lesser frequency compared to current char
                maxAllowedFreqForNextChr = max(currChrFreq - 1, 0);
            }
        }
        
        return minDeletions;
    }
};
