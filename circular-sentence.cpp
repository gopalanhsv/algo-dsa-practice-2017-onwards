class Solution {
public:
    bool
    isCircularSentence(string sentence) {
    
        auto & s = sentence;
        typedef string::size_type strSzT;
        strSzT strSz = s.size();
        if (strSz < 2) {
            return true;
        }
        
        if (s[0] != s[strSz - 1]) {
            // First char does not equal last char => non-circular
            return false;
        }
        
        strSzT i = 0;
        while (i < strSz) {
            // Skip current word letters till word end is reached
            i = s.find(' ', i + 1);
            if (i == string::npos) {
                break;
            }
            auto & prevWordLastChar = s[i - 1];
            // Skip spaces till new word begins
            while ((i < strSz) && isspace(s[i])) {
                ++i;
            }
            if (i >= strSz) {
                break;
            }
            auto & nextWordFirstChar = s[i];
            
            if (prevWordLastChar != nextWordFirstChar) {
                return false;
            }
        }
        
        return true;
    }
};
