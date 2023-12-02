// n => s.size()/t.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    bool
    makeStringsEqual(string s, string target) {
        auto sSz = s.size();
        if (sSz != target.size()) {
            return false;
        }
        
        // Result of selecting 2 indices i, j and applying the operations on them, one gets :-
        // 1. Input (s[i] = 0, s[j] = 0) leads to Output (s[i] = 0, s[j] = 0)
        // 2. Input (s[i] = 0, s[j] = 1) leads to Output (s[i] = 1, s[j] = 1)
        // 3. Input (s[i] = 1, s[j] = 0) leads to Output (s[i] = 1, s[j] = 1)
        // 4. Input (s[i] = 1, s[j] = 1) leads to Output (s[i] = 1, s[j] = 0)
        
        // If 's' is input and 't' is the target 
        // A. For index 'j' where s[j] == t[j], nothing needs to be done
        // B. For index 'j' where s[j] != t[j],
        // (a) s[j] = 0, t[j] = 1, to make s[j] = 1 select any other index 'i' with s[i] = 1
        //     and apply operation 3 => s[i] = 1, s[j] = 1
        // (b) s[j] = 1, t[j] = 0, to make s[j] = 0 select any other index 'i' with s[i] = 1
        //     and apply operation 4 => s[i] = 1, s[j] = 0
        
        // When 's' is all zeroes, then there is no way to turn any of 's' bits to 1
        // (if the target has at least one '1' bit)
        // When 't' is all zeroes, it is possible to convert all bits in 's' except the
        // one to '0'
        
        // Thus if 's' OR 't' are all zeros, equalization is impossible unless they are identical.
        bool onesInS = (s.find('1') != string::npos);
        bool onesInT = (target.find('1') != string::npos);
        
        return (!onesInS && !onesInT) || (onesInS && onesInT);
    }
};
