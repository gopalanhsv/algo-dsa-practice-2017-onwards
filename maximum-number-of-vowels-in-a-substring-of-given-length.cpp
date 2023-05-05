// Time complexity : O(s.size())
// Space complexity : O(1)

class Solution {
public:
    int
    maxVowels(string s, int k) {
    
        // k- sized subtring of 's' is modelled using a fixed sized
        // sliding window of size-k over the string
        // Problem reduces to finding the window with the maximum
        // number of vowels taken over each of the k-sized windows;
        // and selecting that vowel count
        
        // Tracks the maximum number of vowels over each of the 'k'
        // sized substrings seen so far
        int maxVowelCnt = 0;
        // Substring of 's' is represented via sliding window over the
        // closed range [winStart, winEnd]
        // Tracks the number of vowels in the current window/substring
        int currSubstringVowelCnt = 0;
        int winStart = 0;
        for (int winEnd = 0; winEnd != s.size(); ++winEnd) {
            // Advance the right side of the window/substring by
            // one to include the new character
            auto & currChar = s[winEnd];
            // Update the count of vowels in current substring/window
            if (isVowel(currChar)) {
                ++currSubstringVowelCnt;
            }
            
            if (winEnd >= k - 1) {
                // Window/substring size is 'k'
                
                maxVowelCnt = max(maxVowelCnt, currSubstringVowelCnt);
                
                // Advance the start/left side of the window by one character
                // to maintain window size at 'k' for next iteration
                auto & winStartChar = s[winStart++];
                if (isVowel(winStartChar)) {
                    --currSubstringVowelCnt;
                }               
            }
        }
        
        return maxVowelCnt;
    }
    
private:
    
    inline bool
    isVowel(char c) {
        return ('a' == c) || ('e' == c) ||('i' == c) || ('o' == c) || ('u' == c); 
    }
};
