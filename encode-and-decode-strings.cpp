class Codec {
public:

    // Encodes a list of strings to a single string.
    string
    encode(vector<string>& strs) {
        // Use '#' as join character between two strings
        // Use 'a' as escape character
        // 1. Wherever a '#' occurs in the original string, 
        //    escape it by adding 'a' prior to it
        // 2. Wherever a 'a' occurs in the original string, 
        //    escape it by adding 'a' prior to it
        // 3. Wherever a new string vector begins, add a # prior to
        //    it to encode the fact that a new string vector begins
        string encStr;
        for (auto & str : strs) {
            encStr += "#";
            for (auto & ch : str) {
                if (ch == 'a') {
                    encStr += "aa";    
                } else if (ch == '#') {
                    encStr += "a#";
                } else {
                    encStr += ch;
                }
            }
        }
        return encStr;
    }

    // Decodes a single string to a list of strings.
    vector<string>
    decode(string s) {
        // Based on the encoding rules, decode as follows:-
        // 1. Wherever a '#' occurs in the string, without
        //    any previous 'a' escape character, copy the string being
        //    decoded to the output vector; and commence a new
        //    string to copy the decoded chars post the '#' char
        // 2. Wherever a 'a' is encountered in the string, drop it
        //    and keep the character next to it in the string
        vector<string> outV;
        string currStr;
        for (int i = 1; i != s.size(); ++i) {
            if (s[i] == '#') {
                // End of current string and start of new string
                outV.emplace_back(currStr);
                currStr = "";
            } else if (s[i] == 'a') {
                // Drop this escape char and store next char
                currStr += s[++i];
            } else {
                currStr += s[i];
            }
        }
        // last portion of encoded string has to be stored
        outV.emplace_back(currStr);   
        return outV;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
