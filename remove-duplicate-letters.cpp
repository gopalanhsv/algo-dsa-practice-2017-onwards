// n <=> s.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    string
    removeDuplicateLetters(string s) {
        // Build hash table tracking the index locations
        // of last occurence of each letter
        unordered_map<char, int> lastOccurPosTbl;
        for (int i = 0; i != s.size(); ++i) {
            lastOccurPosTbl[s[i]] = i;
        }
        
        // Iterate over the string sequentially from L->R
        // At each location 'i', adopt the greedy approach of selecting only
        // the subsequence of chars from s[0, i] which is smallest lexicographically
        // with duplicate chars removed
        // Use a stack to construct the smallest subsequence possible till current
        // char (seen from bottom to top of stack)
        stack<char> stk;
        // Frequency count of chars present in the stack/subsequence selected
        unordered_map<char, int> stkChrFreqCnt;
        // Iterate over the string sequentially from L->R
        for (int i = 0; i != s.size(); ++i) {
            auto & currChr = s[i];
            
            if (stkChrFreqCnt[currChr] > 0) {
                // Skip current char as it is already selected in subsequence
                continue;
            }
            
            // Make the subsequence lexicographically the smallest possibly for s[0, i]
            while (!stk.empty() && (currChr < stk.top()) && (lastOccurPosTbl[stk.top()] > i)) {
                // Drop chars in the constructed subsequence which are lexicographically larger than
                // current char if they occur later in the string => Later occurrence can be selected
                stkChrFreqCnt[stk.top()]--;
                stk.pop();
            }
            if (!stkChrFreqCnt[currChr]) {
                // Add current char to end of subsequence only if it has not occured earlier
                stk.push(currChr);
                stkChrFreqCnt[currChr]++;
            }
        }
        
        // Build string for the smallest subsequence 
        auto smallestSubSeqSz = stk.size();
        string outStr;
        outStr.resize(smallestSubSeqSz);
        auto wrIdx = smallestSubSeqSz - 1;
        while (!stk.empty()) {
            outStr[wrIdx--] = stk.top();
            stk.pop();
        }
        
        return outStr;
    }
};
