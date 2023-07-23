// n => total number of chars across all words 
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    vector<string>
    splitWordsBySeparator(vector<string>& words, char separator) {
        vector<string> outV;
        // Iterate over words in the array
        for (auto & word : words) {
            // Tracks the current running string formed by
            // chars since the last encountered separator
            string splitStr;
            // Iterate over the word chars from L->R
            for (auto & c : word) {
                if (c == separator) {
                    // Current char is a separator
                    if (!splitStr.empty()) {
                        // Non empty sub-string between current and its immediate previous
                        // separator. Store sub-string and reset it to a empty string
                        outV.emplace_back(splitStr);
                        splitStr = "";
                    }
                } else {
                    // Current char is not a separator. Adding to current running string
                    // since last separator
                    splitStr += c;
                }
            }

            // End of current running word in the array (which in itself is a seperator)
            if (!splitStr.empty()) {
                // Non empty sub-string between from immediate previous separator till 
                // end of word. Store sub-string
                outV.emplace_back(splitStr);
            }
        }
        
        return outV;
    }
};
