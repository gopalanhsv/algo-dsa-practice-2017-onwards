class Solution {
public:
    int
    lengthOfLongestSubstring(string s) {
    
        // Using a sliding window over the string to represent a
        // substring having no repeated chars
        // Sliding window is represented via a hash table
        unordered_set<char> substrChars;
        int winStart = 0;
        int maxLen = 0;
        // Iterate over the string chars sequentially from L->R
        for (int winEnd = 0; winEnd != s.size(); ++winEnd) {
            // Attempt to add current char to the right of the sliding window
            auto & currChr = s[winEnd];
            // If an instance of the current char was already present in the
            // window, shrink the window from left till the previous instance
            // of the char gets eliminated. The window will now have no
            // repeated chars
            while ((winStart < winEnd) &&
                   (substrChars.find(currChr) != substrChars.end())){
                substrChars.erase(s[winStart++]);
            }
            
            // Add new char to window/string
            // Compute window length; and update the max len seen
            maxLen = max(maxLen, winEnd - winStart + 1);
            substrChars.insert(currChr);
        }
        return maxLen;
    }
};
