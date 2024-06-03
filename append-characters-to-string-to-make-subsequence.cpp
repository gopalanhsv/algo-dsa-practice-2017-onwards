// m = s.size(), n = t.size()
// Time complexity : O(max(m, n))
// Space complexity : O(1)

class Solution {
public:
    int
    appendCharacters(string s, string t) {
        auto textIdx = 0;
        auto patternIdx = 0;
        auto textSz = s.size();
        auto patternSz = t.size();

        // Iterate over the search pattern 't' chars sequentially from L->R
        while ((textIdx < textSz) && (patternIdx < patternSz)) {
            // Look for closest location of current search pattern text char in
            // in the text string 's' which is located immediately after the
            // previously found char of 't' in 's'
            textIdx = s.find(t[patternIdx], textIdx);
            if (textIdx == string::npos) {
                // End of text string reached => patterns chars in t[patternIdx, ..]
                // need to be appended to 's'
                break;
            }
            
            // Current search pattern char t[patternIdx] found in search text
            // Advance to next pattern char and advance the search location in
            // search text too
            ++textIdx;
            ++patternIdx;
        }
        
        return patternSz - patternIdx;
    }
};
