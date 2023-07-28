// Time complexity : O(s.size()) / O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    minimizedStringLength(string s) {
        // Repeat the ops randomly choosing a character in the string and 
        // deleting its nearest occurence to left + right results in the final string
        // having only a single occurrence of each character initially present
        // i.e. a list of unique chars present in the string
        unordered_set<int> uniqueCharsTbl;
        for (auto & c : s) {
            uniqueCharsTbl.insert(c);
        }
        return uniqueCharsTbl.size();
    }
};
