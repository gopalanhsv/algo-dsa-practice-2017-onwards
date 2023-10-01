// Time complexity : O(s.size())
// Space complexity : O(1)

class Solution {
public:
    string
    reverseWords(string s) {
        
        // Reverse each word within string one word at a time
        typedef string::size_type strSzT;
        strSzT strSz = s.size();
        strSzT wStart = 0;
        strSzT wEnd = 0;
        while (wEnd < strSz) {
            
            // Find end of current word
            wEnd = s.find(' ', wEnd);
            if (wEnd == string::npos) {
                wEnd = strSz;
            }
            
            // Reverse the substring delimited by [wStart, wEnd]
            reverse(s.begin() + wStart, s.begin() + wEnd);

            // Skip spaces till the beginning of next word
            wStart = wEnd;
            while (isspace(s[wStart])) {
                ++wStart;
            }
            wEnd = wStart;
        }
        
        return s;
    }
};
